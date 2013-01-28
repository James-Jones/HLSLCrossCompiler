
#include "reflect.h"
#include "debug.h"
#include <stdlib.h>

static void ReadStringFromTokenStream(const uint32_t* tokens, char* str)
{
    char* charTokens = (char*) tokens;
    char nextCharacter = *charTokens++;
    int length = 0;

    //Add each individual character until
    //a terminator is found.
    while(nextCharacter != 0) {

        str[length++] = nextCharacter;

        if(length > MAX_REFLECT_STRING_LENGTH)
        {
            str[length-1] = '\0';
            return;
        }

        nextCharacter = *charTokens++;
    }

    str[length] = '\0';
}

static void ReadInputSignatures(const uint32_t* pui32Tokens,
                        ShaderInfo* psShaderInfo)
{
    uint32_t i;

    InOutSignature* psSignatures;
    const uint32_t* pui32FirstSignatureToken = pui32Tokens;
    const uint32_t ui32ElementCount = *pui32Tokens++;
    const uint32_t ui32Key = *pui32Tokens++;

    psSignatures = malloc(sizeof(InOutSignature) * ui32ElementCount);
    psShaderInfo->psInputSignatures = psSignatures;
    psShaderInfo->ui32NumInputSignatures = ui32ElementCount;

    for(i=0; i<ui32ElementCount; ++i)
    {
        InOutSignature* psCurrentSignature = psSignatures + i;
        const uint32_t ui32SemanticNameOffset = *pui32Tokens++;
        psCurrentSignature->ui32SymanticIndex = *pui32Tokens++;
        psCurrentSignature->ui32SymanticValueType = *pui32Tokens++;
        psCurrentSignature->ui32ComponentType = *pui32Tokens++;
        psCurrentSignature->ui32Register = *pui32Tokens++;
        psCurrentSignature->ui32Mask = *pui32Tokens++;

        ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstSignatureToken+ui32SemanticNameOffset), psCurrentSignature->SymanticName);
    }
}

static const uint32_t* ReadResourceBinding(const uint32_t* pui32FirstResourceToken, const uint32_t* pui32Tokens, ResourceBinding* psBinding)
{
    uint32_t ui32NameOffset = *pui32Tokens++;

    ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstResourceToken+ui32NameOffset), psBinding->Name);

    psBinding->eType = *pui32Tokens++;
    psBinding->ui32ReturnType = *pui32Tokens++;
    psBinding->eDimension = (RESOURCE_DIMENSION)*pui32Tokens++;
    psBinding->ui32NumSamples = *pui32Tokens++;
    psBinding->ui32BindPoint = *pui32Tokens++;
    psBinding->ui32BindCount = *pui32Tokens++;
    psBinding->ui32Flags = *pui32Tokens++;

    return pui32Tokens;
}

static const uint32_t* ReadConstantBuffer(const uint32_t* pui32FirstConstBufToken, const uint32_t* pui32Tokens, ConstantBuffer* psBuffer)
{
    uint32_t i;
    uint32_t ui32NameOffset = *pui32Tokens++;    
    uint32_t ui32VarCount = *pui32Tokens++;
    uint32_t ui32VarOffset = *pui32Tokens++;
    const uint32_t* pui32VarToken = (const uint32_t*)((const char*)pui32FirstConstBufToken+ui32VarOffset);

    ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstConstBufToken+ui32NameOffset), psBuffer->Name);

    psBuffer->ui32NumVars = ui32VarCount;

    for(i=0; i<ui32VarCount; ++i)
    {
        ShaderVar * const psVar = &psBuffer->asVars[i];

        uint32_t ui32StartOffset;
        uint32_t ui32Size;
        uint32_t ui32Flags;
        uint32_t ui32TypeOffset;
        uint32_t ui32DefaultValueOffset;

        ui32NameOffset = *pui32VarToken++;

        ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstConstBufToken+ui32NameOffset), psVar->Name);

        ui32StartOffset = *pui32VarToken++;
        ui32Size = *pui32VarToken++;
        ui32Flags = *pui32VarToken++;
        ui32TypeOffset = *pui32VarToken++;

        ui32DefaultValueOffset = *pui32VarToken++;

        if(ui32DefaultValueOffset)
        {
            if(ui32Size == 4)
            {
                const uint32_t* DefaultValToken = (const uint32_t*)((const char*)pui32FirstConstBufToken+ui32DefaultValueOffset);

                psVar->ui32DefaultValue = *DefaultValToken;
            }
        }
    }

    {
        uint32_t ui32Size = *pui32Tokens++;
        uint32_t ui32Flags = *pui32Tokens++;
        uint32_t ui32BufferType = *pui32Tokens++;
    }

    return pui32Tokens;
}

static void ReadResources(const uint32_t* pui32Tokens,//in
                   ShaderInfo* psShaderInfo)//out
{
    ResourceBinding* psResBindings;
    ConstantBuffer* psConstantBuffers;
    const uint32_t* pui32ConstantBuffers;
    const uint32_t* pui32ResourceBindings;
    const uint32_t* pui32FirstToken = pui32Tokens;
    uint32_t i;

    const uint32_t ui32NumConstantBuffers = *pui32Tokens++;
    const uint32_t ui32ConstantBufferOffset = *pui32Tokens++;

    uint32_t ui32NumResourceBindings = *pui32Tokens++;
    uint32_t ui32ResourceBindingOffset = *pui32Tokens++;
    uint32_t ui32ShaderModel = *pui32Tokens++;
    uint32_t ui32CompileFlags = *pui32Tokens++;//D3DCompile flags? http://msdn.microsoft.com/en-us/library/gg615083(v=vs.85).aspx

    //Resources
    pui32ResourceBindings = (const uint32_t*)((const char*)pui32FirstToken + ui32ResourceBindingOffset);

    psResBindings = malloc(sizeof(ResourceBinding)*ui32NumResourceBindings);

    psShaderInfo->ui32NumResourceBindings = ui32NumResourceBindings;
    psShaderInfo->psResourceBindings = psResBindings;

    for(i=0; i < ui32NumResourceBindings; ++i)
    {
        pui32ResourceBindings = ReadResourceBinding(pui32FirstToken, pui32ResourceBindings, psResBindings+i);
    }

    //Constant buffers
    pui32ConstantBuffers = (const uint32_t*)((const char*)pui32FirstToken + ui32ConstantBufferOffset);

    psConstantBuffers = malloc(sizeof(ConstantBuffer) * ui32NumConstantBuffers);

    psShaderInfo->ui32NumConstantBuffers = ui32NumConstantBuffers;
    psShaderInfo->psConstantBuffers = psConstantBuffers;

    for(i=0; i < ui32NumConstantBuffers; ++i)
    {
        pui32ConstantBuffers = ReadConstantBuffer(pui32FirstToken, pui32ConstantBuffers, psConstantBuffers+i);
    }
}

void GetConstantBufferFromBindingPoint(const uint32_t ui32BindPoint, const ShaderInfo* psShaderInfo, ConstantBuffer** ppsConstBuf)
{
    ASSERT(ui32BindPoint < psShaderInfo->ui32NumConstantBuffers);
    *ppsConstBuf = psShaderInfo->psConstantBuffers + ui32BindPoint;
}

int GetResourceFromBindingPoint(ResourceType eType, uint32_t ui32BindPoint, ShaderInfo* psShaderInfo, ResourceBinding** ppsOutBinding)
{
    uint32_t i;
    const uint32_t ui32NumBindings = psShaderInfo->ui32NumResourceBindings;
    ResourceBinding* psBindings = psShaderInfo->psResourceBindings;

    for(i=0; i<ui32NumBindings; ++i)
    {
        if(psBindings[i].eType == eType)
        {
			if(ui32BindPoint >= psBindings[i].ui32BindPoint && ui32BindPoint < (psBindings[i].ui32BindPoint + psBindings[i].ui32BindCount))
			{
				*ppsOutBinding = psBindings + i;
				return 1;
			}
        }
    }
    return 0;
}

void LoadShaderInfo(const uint32_t* pui32Inputs, const uint32_t* pui32Resources,
    ShaderInfo* psInfo)
{
    if(pui32Inputs)
        ReadInputSignatures(pui32Inputs, psInfo);
    if(pui32Resources)
        ReadResources(pui32Resources, psInfo);
}

void FreeShaderInfo(ShaderInfo* psShaderInfo)
{
    free(psShaderInfo->psInputSignatures);
    free(psShaderInfo->psResourceBindings);
    free(psShaderInfo->psConstantBuffers);

    psShaderInfo->ui32NumInputSignatures = 0;
    psShaderInfo->ui32NumResourceBindings = 0;
    psShaderInfo->ui32NumConstantBuffers = 0;
}

#if 0
switch(type)
{

    glGetSubroutineUniformLocation
    glGetSubroutineIndex


    uint32_t ui32Program;

    glGetIntegerv(GL_CURRENT_PROGRAM, &ui32Program);

    uint32_t ui32Location = glGetUniformLocation(program, Name);

    case RTYPE_CBUFFER:
    {
        break;
    }
    case RTYPE_TBUFFER:
    {
        break;
    }
    case RTYPE_TEXTURE:
    {
        break;
    }
    case RTYPE_SAMPLER:
    {
        break;
    }
    case RTYPE_UAV_RWTYPED:
    {
        break;
    }
    case RTYPE_STRUCTURED:
    {
        break;
    }
    case RTYPE_UAV_RWSTRUCTURED:
    {
        break;
    }
    case RTYPE_BYTEADDRESS:
    {
        break;
    }
    case RTYPE_UAV_RWBYTEADDRESS:
    {
        break;
    }
    case RTYPE_UAV_APPEND_STRUCTURED:
    {
        break;
    }
    case RTYPE_UAV_CONSUME_STRUCTURED:
    {
        break;
    }
    case RTYPE_UAV_RWSTRUCTURED_WITH_COUNTER:
    {
        break;
    }
}
#endif
