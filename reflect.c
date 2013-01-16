
#include "reflect.h"
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

void ReadInputSignatures(const uint32_t* pui32Tokens,
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

void ReadResources(const uint32_t* pui32Tokens,//in
                   ShaderInfo* psShaderInfo)//out
{
    ResourceBinding* psBindings;
    const uint32_t* pui32ConstantBuffers;
    const uint32_t* pui32ResourceBindings;
    const uint32_t* pui32FirstToken = pui32Tokens;
    uint32_t i;

    uint32_t ui32NumConstantBuffers = *pui32Tokens++;
    uint32_t ui32ConstantBufferOffset = *pui32Tokens++;

    uint32_t ui32NumResourceBindings = *pui32Tokens++;
    uint32_t ui32ResourceBindingOffset = *pui32Tokens++;
    uint32_t ui32ShaderModel = *pui32Tokens++;
    uint32_t ui32CompileFlags = *pui32Tokens++;//D3DCompile flags? http://msdn.microsoft.com/en-us/library/gg615083(v=vs.85).aspx

    pui32ConstantBuffers = (const uint32_t*)((const char*)pui32FirstToken + ui32ConstantBufferOffset);
    pui32ResourceBindings = (const uint32_t*)((const char*)pui32FirstToken + ui32ResourceBindingOffset);

    psBindings = malloc(sizeof(ResourceBinding)*ui32NumResourceBindings);

    psShaderInfo->ui32NumResourceBindings = ui32NumResourceBindings;
    psShaderInfo->psResourceBindings = psBindings;

    for(i=0; i < ui32NumResourceBindings; ++i)
    {
        pui32ResourceBindings = ReadResourceBinding(pui32FirstToken, pui32ResourceBindings, psBindings+i);
    }
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

void FreeShaderInfo(ShaderInfo* psShaderInfo)
{
    free(psShaderInfo->psInputSignatures);
    free(psShaderInfo->psResourceBindings);

    psShaderInfo->ui32NumInputSignatures = 0;
    psShaderInfo->ui32NumResourceBindings = 0;
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
