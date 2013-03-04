
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

static const uint32_t* ReadConstantBuffer(ShaderInfo* psShaderInfo,
    const uint32_t* pui32FirstConstBufToken, const uint32_t* pui32Tokens, ConstantBuffer* psBuffer)
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
        //D3D11_SHADER_VARIABLE_DESC
        ShaderVar * const psVar = &psBuffer->asVars[i];

        uint32_t ui32Flags;
        uint32_t ui32TypeOffset;
        uint32_t ui32DefaultValueOffset;

        ui32NameOffset = *pui32VarToken++;

        ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstConstBufToken+ui32NameOffset), psVar->Name);

        psVar->ui32StartOffset = *pui32VarToken++;
        psVar->ui32Size = *pui32VarToken++;
        ui32Flags = *pui32VarToken++;
        ui32TypeOffset = *pui32VarToken++;

        ui32DefaultValueOffset = *pui32VarToken++;


		if (psShaderInfo->ui32MajorVersion  >= 5)
		{
			uint32_t StartTexture = *pui32VarToken++;
			uint32_t TextureSize = *pui32VarToken++;
			uint32_t StartSampler = *pui32VarToken++;
			uint32_t SamplerSize = *pui32VarToken++;
		}

        if(ui32DefaultValueOffset)
        {
            if(psVar->ui32Size == 4)
            {
                const uint32_t* pui32DefaultValToken = (const uint32_t*)((const char*)pui32FirstConstBufToken+ui32DefaultValueOffset);

                psVar->ui32DefaultValue = *pui32DefaultValToken;
            }
        }

        if(ui32TypeOffset)
        {
            //D3D11_SHADER_TYPE_DESC
            const uint16_t* pui16TypeToken = (const uint16_t*)((const char*)pui32FirstConstBufToken+ui32TypeOffset);

            uint16_t varClass = *pui16TypeToken++;
            uint16_t varType = *pui16TypeToken++;

            uint16_t varRows = *pui16TypeToken++;
            uint16_t varCols = *pui16TypeToken++;

            uint16_t varElemCount = *pui16TypeToken++;
            uint16_t varMemberCount = *pui16TypeToken++;

            uint32_t varMemberOffset = *pui16TypeToken++ << 16;
            varMemberOffset |= *pui16TypeToken++;
        }
    }


    {
        uint32_t ui32Flags;
        uint32_t ui32BufferType;

        psBuffer->ui32TotalSizeInBytes = *pui32Tokens++;
        ui32Flags = *pui32Tokens++;
        ui32BufferType = *pui32Tokens++;
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
    uint32_t i, k;

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

    k=0;
    for(i=0; i < ui32NumResourceBindings; ++i)
    {
        pui32ResourceBindings = ReadResourceBinding(pui32FirstToken, pui32ResourceBindings, psResBindings+i);

        if(psResBindings[i].eType == RTYPE_CBUFFER)
        {
            ASSERT(k < MAX_CBUFFERS);
            psShaderInfo->aui32ConstBufferBindpointRemap[psResBindings[i].ui32BindPoint] = k++;
        }
    }

    //Constant buffers
    pui32ConstantBuffers = (const uint32_t*)((const char*)pui32FirstToken + ui32ConstantBufferOffset);

    psConstantBuffers = malloc(sizeof(ConstantBuffer) * ui32NumConstantBuffers);

    psShaderInfo->ui32NumConstantBuffers = ui32NumConstantBuffers;
    psShaderInfo->psConstantBuffers = psConstantBuffers;

    for(i=0; i < ui32NumConstantBuffers; ++i)
    {
        pui32ConstantBuffers = ReadConstantBuffer(psShaderInfo, pui32FirstToken, pui32ConstantBuffers, psConstantBuffers+i);
    }
}

static const uint16_t* ReadClassType(const uint32_t* pui32FirstInterfaceToken, const uint16_t* pui16Tokens, ClassType* psClassType)
{
    const uint32_t* pui32Tokens = (const uint32_t*)pui16Tokens;
    uint32_t ui32NameOffset = *pui32Tokens;
    pui16Tokens+= 2;

    psClassType->ui16ID = *pui16Tokens++;
    psClassType->ui16ConstBufStride = *pui16Tokens++;
    psClassType->ui16Texture = *pui16Tokens++;
    psClassType->ui16Sampler = *pui16Tokens++;

    ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstInterfaceToken+ui32NameOffset), psClassType->Name);

    return pui16Tokens;
}

static const uint16_t* ReadClassInstance(const uint32_t* pui32FirstInterfaceToken, const uint16_t* pui16Tokens, ClassInstance* psClassInstance)
{
    uint32_t ui32NameOffset = *pui16Tokens++ << 16;
    ui32NameOffset |= *pui16Tokens++;

    psClassInstance->ui16ID = *pui16Tokens++;
    psClassInstance->ui16ConstBuf = *pui16Tokens++;
    psClassInstance->ui16ConstBufOffset = *pui16Tokens++;
    psClassInstance->ui16Texture = *pui16Tokens++;
    psClassInstance->ui16Sampler = *pui16Tokens++;

    ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstInterfaceToken+ui32NameOffset), psClassInstance->Name);

    return pui16Tokens;
}


static void ReadInterfaces(const uint32_t* pui32Tokens,
                        ShaderInfo* psShaderInfo)
{
    uint32_t i;
    uint32_t ui32StartSlot;
    const uint32_t* pui32FirstInterfaceToken = pui32Tokens;
    const uint32_t ui32ClassInstanceCount = *pui32Tokens++;
    const uint32_t ui32ClassTypeCount = *pui32Tokens++;
    const uint32_t ui32InterfaceSlotRecordCount = *pui32Tokens++;
    const uint32_t ui32InterfaceSlotCount = *pui32Tokens++;
    const uint32_t ui32ClassInstanceOffset = *pui32Tokens++;
    const uint32_t ui32ClassTypeOffset = *pui32Tokens++;
    const uint32_t ui32InterfaceSlotOffset = *pui32Tokens++;

    const uint16_t* pui16ClassTypes = (const uint16_t*)((const char*)pui32FirstInterfaceToken + ui32ClassTypeOffset);
    const uint16_t* pui16ClassInstances = (const uint16_t*)((const char*)pui32FirstInterfaceToken + ui32ClassInstanceOffset);
    const uint32_t* pui32InterfaceSlots = (const uint32_t*)((const char*)pui32FirstInterfaceToken + ui32InterfaceSlotOffset);

    const uint32_t* pui32InterfaceSlotTokens = pui32InterfaceSlots;

    ClassType* psClassTypes;
    ClassInstance* psClassInstances;

    psClassTypes = malloc(sizeof(ClassType) * ui32ClassTypeCount);
    for(i=0; i<ui32ClassTypeCount; ++i)
    {
        pui16ClassTypes = ReadClassType(pui32FirstInterfaceToken, pui16ClassTypes, psClassTypes+i);
        psClassTypes[i].ui16ID = (uint16_t)i;
    }

    psClassInstances = malloc(sizeof(ClassType) * ui32ClassInstanceCount);
    for(i=0; i<ui32ClassInstanceCount; ++i)
    {
        pui16ClassInstances = ReadClassInstance(pui32FirstInterfaceToken, pui16ClassInstances, psClassInstances+i);
    }

    //Slots map function table to $ThisPointer cbuffer variable index
    ui32StartSlot = 0;
    for(i=0; i<ui32InterfaceSlotRecordCount;++i)
    {
        uint32_t k;
        
        const uint32_t ui32SlotSpan = *pui32InterfaceSlotTokens++;
        const uint32_t ui32Count = *pui32InterfaceSlotTokens++;
        const uint32_t ui32TypeIDOffset = *pui32InterfaceSlotTokens++;
        const uint32_t ui32TableIDOffset = *pui32InterfaceSlotTokens++;

        const uint16_t* pui16TypeID = (const uint16_t*)((const char*)pui32FirstInterfaceToken+ui32TypeIDOffset);
        const uint32_t* pui32TableID = (const uint32_t*)((const char*)pui32FirstInterfaceToken+ui32TableIDOffset);

        for(k=0; k < ui32Count; ++k)
        {
            psShaderInfo->aui32TableIDToTypeID[*pui32TableID++] = *pui16TypeID++;
        }

        ui32StartSlot += ui32SlotSpan;
    }

    psShaderInfo->ui32NumClassInstances = ui32ClassInstanceCount;
    psShaderInfo->psClassInstances = psClassInstances;

    psShaderInfo->ui32NumClassTypes = ui32ClassTypeCount;
    psShaderInfo->psClassTypes = psClassTypes;
}

void GetConstantBufferFromBindingPoint(const uint32_t ui32BindPoint, const ShaderInfo* psShaderInfo, ConstantBuffer** ppsConstBuf)
{
    uint32_t index;
    
    ASSERT(ui32BindPoint < MAX_CBUFFERS);
    
    index = psShaderInfo->aui32ConstBufferBindpointRemap[ui32BindPoint]; 
    
    ASSERT(index < psShaderInfo->ui32NumConstantBuffers);
    
    *ppsConstBuf = psShaderInfo->psConstantBuffers + index;
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

int GetInterfaceVarFromOffset(uint32_t ui32Offset, ShaderInfo* psShaderInfo, ShaderVar** ppsShaderVar)
{
    uint32_t i;
    ConstantBuffer* psThisPointerConstBuffer = psShaderInfo->psThisPointerConstBuffer;

    const uint32_t ui32NumVars = psThisPointerConstBuffer->ui32NumVars;

    for(i=0; i<ui32NumVars; ++i)
    {
        if(ui32Offset >= psThisPointerConstBuffer->asVars[i].ui32StartOffset && 
            ui32Offset < (psThisPointerConstBuffer->asVars[i].ui32StartOffset + psThisPointerConstBuffer->asVars[i].ui32Size))
	    {
		    *ppsShaderVar = &psThisPointerConstBuffer->asVars[i];
		    return 1;
	    }
    }
    return 0;
}

void LoadShaderInfo(const uint32_t ui32MajorVersion,
    const uint32_t ui32MinorVersion,
    const uint32_t* pui32Inputs, const uint32_t* pui32Resources,
    const uint32_t* pui32Interfaces, ShaderInfo* psInfo)
{
    psInfo->eTessOutPrim = TESSELLATOR_OUTPUT_UNDEFINED;
    psInfo->eTessPartitioning = TESSELLATOR_PARTITIONING_UNDEFINED;

    psInfo->ui32MajorVersion = ui32MajorVersion;
    psInfo->ui32MinorVersion = ui32MinorVersion;


    if(pui32Inputs)
        ReadInputSignatures(pui32Inputs, psInfo);
    if(pui32Resources)
        ReadResources(pui32Resources, psInfo);
    if(pui32Interfaces)
        ReadInterfaces(pui32Interfaces, psInfo);

    {
        uint32_t i;
        for(i=0; i<psInfo->ui32NumConstantBuffers;++i)
        {
            bstring cbufName = bfromcstr(&psInfo->psConstantBuffers[i].Name[0]);
            bstring cbufThisPointer = bfromcstr("$ThisPointer");
            if(bstrcmp(cbufName, cbufThisPointer) == 0)
            {
                psInfo->psThisPointerConstBuffer = &psInfo->psConstantBuffers[i];
            }
        }
    }
}

void FreeShaderInfo(ShaderInfo* psShaderInfo)
{
    free(psShaderInfo->psInputSignatures);
    free(psShaderInfo->psResourceBindings);
    free(psShaderInfo->psConstantBuffers);
    free(psShaderInfo->psClassTypes);
    free(psShaderInfo->psClassInstances);

    psShaderInfo->ui32NumInputSignatures = 0;
    psShaderInfo->ui32NumResourceBindings = 0;
    psShaderInfo->ui32NumConstantBuffers = 0;
    psShaderInfo->ui32NumClassTypes = 0;
    psShaderInfo->ui32NumClassInstances = 0;
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
