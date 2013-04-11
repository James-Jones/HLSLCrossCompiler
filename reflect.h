#ifndef REFLECT_H
#define REFLECT_H

#include "tokens.h"
#include "bstrlib.h"

#define MAX_REFLECT_STRING_LENGTH 512
#define MAX_SHADER_VARS 256
#define MAX_CBUFFERS 256
#define MAX_FUNCTION_TABLES 256

typedef enum { 
  INOUT_COMPONENT_UNKNOWN  = 0,
  INOUT_COMPONENT_UINT32   = 1,
  INOUT_COMPONENT_SINT32   = 2,
  INOUT_COMPONENT_FLOAT32  = 3
} INOUT_COMPONENT_TYPE;

typedef struct InOutSignature_TAG
{
    char SymanticName[MAX_REFLECT_STRING_LENGTH];
    uint32_t ui32SymanticIndex;
    uint32_t ui32SymanticValueType;
    INOUT_COMPONENT_TYPE eComponentType;
    uint32_t ui32Register;
    uint32_t ui32Mask;
    uint32_t ui32ReadWriteMask;
} InOutSignature;

typedef enum ResourceType_TAG
{
    RTYPE_CBUFFER,//0
    RTYPE_TBUFFER,//1
    RTYPE_TEXTURE,//2
    RTYPE_SAMPLER,//3
    RTYPE_UAV_RWTYPED,//4
    RTYPE_STRUCTURED,//5
    RTYPE_UAV_RWSTRUCTURED,//6
    RTYPE_BYTEADDRESS,//7
    RTYPE_UAV_RWBYTEADDRESS,//8
    RTYPE_UAV_APPEND_STRUCTURED,//9
    RTYPE_UAV_CONSUME_STRUCTURED,//10
    RTYPE_UAV_RWSTRUCTURED_WITH_COUNTER,//11
} ResourceType;

typedef struct ResourceBinding_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];
    ResourceType eType;
    uint32_t ui32BindPoint;
    uint32_t ui32BindCount;
    uint32_t ui32Flags;
    RESOURCE_DIMENSION eDimension;
    uint32_t ui32ReturnType;
    uint32_t ui32NumSamples;
} ResourceBinding;

typedef struct ShaderVar_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];
    uint32_t ui32DefaultValue;
    uint32_t ui32StartOffset;
    uint32_t ui32Size;
} ShaderVar;

typedef struct ConstantBuffer_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];

    uint32_t ui32NumVars;
    ShaderVar asVars [MAX_SHADER_VARS];

    uint32_t ui32TotalSizeInBytes;
} ConstantBuffer;

typedef struct ClassType_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];
    uint16_t ui16ID;
    uint16_t ui16ConstBufStride;
    uint16_t ui16Texture;
    uint16_t ui16Sampler;
} ClassType;

typedef struct ClassInstance_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];
    uint16_t ui16ID;
    uint16_t ui16ConstBuf;
    uint16_t ui16ConstBufOffset;
    uint16_t ui16Texture;
    uint16_t ui16Sampler;
} ClassInstance;

typedef struct ShaderInfo_TAG
{
    uint32_t ui32MajorVersion;
    uint32_t ui32MinorVersion;

    uint32_t ui32NumInputSignatures;
    InOutSignature* psInputSignatures;

    uint32_t ui32NumOutputSignatures;
    InOutSignature* psOutputSignatures;

    uint32_t ui32NumResourceBindings;
    ResourceBinding* psResourceBindings;

    uint32_t ui32NumConstantBuffers;
    ConstantBuffer* psConstantBuffers;
    ConstantBuffer* psThisPointerConstBuffer;

    uint32_t ui32NumClassTypes;
    ClassType* psClassTypes;

    uint32_t ui32NumClassInstances;
    ClassInstance* psClassInstances;

    //Func table ID to class name ID.
    uint32_t aui32TableIDToTypeID[MAX_FUNCTION_TABLES];

    uint32_t aui32ConstBufferBindpointRemap[MAX_CBUFFERS];

    TESSELLATOR_PARTITIONING eTessPartitioning;
    TESSELLATOR_OUTPUT_PRIMITIVE eTessOutPrim;
} ShaderInfo;

int GetResourceFromBindingPoint(ResourceType eType, uint32_t ui32BindPoint, ShaderInfo* psShaderInfo, ResourceBinding** ppsOutBinding);

void GetConstantBufferFromBindingPoint(const uint32_t ui32BindPoint, const ShaderInfo* psShaderInfo, ConstantBuffer** ppsConstBuf);

int GetInterfaceVarFromOffset(uint32_t ui32Offset, ShaderInfo* psShaderInfo, ShaderVar** ppsShaderVar);

typedef struct
{
    uint32_t* pui32Inputs;
    uint32_t* pui32Outputs;
    uint32_t* pui32Resources;
    uint32_t* pui32Interfaces;
} ReflectionChunks;

void LoadShaderInfo(const uint32_t ui32MajorVersion,
    const uint32_t ui32MinorVersion,
    const ReflectionChunks* psChunks,
    ShaderInfo* psInfo);

void FreeShaderInfo(ShaderInfo* psShaderInfo);

#if 0
//--- Utility functions ---

//Returns 0 if not found, 1 otherwise.
int GetResourceFromName(const char* name, ShaderInfo* psShaderInfo, ResourceBinding* psBinding);

//These call into OpenGL and modify the uniforms of the currently bound program.
void SetResourceValueF(ResourceBinding* psBinding, float* value);
void SetResourceValueI(ResourceBinding* psBinding, int* value);
void SetResourceValueStr(ResourceBinding* psBinding, char* value); //Used for interfaces/subroutines. Also for constant buffers?

void CreateUniformBufferObjectFromResource(ResourceBinding* psBinding, uint32_t* ui32GLHandle);
//------------------------
#endif

#endif

