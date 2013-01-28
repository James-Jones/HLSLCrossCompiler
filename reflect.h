#ifndef REFLECT_H
#define REFLECT_H

#include "tokens.h"
#include "bstrlib.h"

#define MAX_REFLECT_STRING_LENGTH 512
#define MAX_SHADER_VARS 256

typedef struct InOutSignature_TAG
{
    char SymanticName[MAX_REFLECT_STRING_LENGTH];
    uint32_t ui32SymanticIndex;
    uint32_t ui32SymanticValueType;
    uint32_t ui32ComponentType;
    uint32_t ui32Register;
    uint32_t ui32Mask;
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
} ShaderVar;

typedef struct ConstantBuffer_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];

    uint32_t ui32NumVars;
    ShaderVar asVars [MAX_SHADER_VARS];
} ConstantBuffer;

typedef struct ShaderInfo_TAG
{
    uint32_t ui32NumInputSignatures;
    InOutSignature* psInputSignatures;

    uint32_t ui32NumResourceBindings;
    ResourceBinding* psResourceBindings;

    uint32_t ui32NumConstantBuffers;
    ConstantBuffer* psConstantBuffers;
} ShaderInfo;

int GetResourceFromBindingPoint(ResourceType eType, uint32_t ui32BindPoint, ShaderInfo* psShaderInfo, ResourceBinding** ppsOutBinding);

void GetConstantBufferFromBindingPoint(const uint32_t ui32BindPoint, const ShaderInfo* psShaderInfo, ConstantBuffer** ppsConstBuf);

void LoadShaderInfo(const uint32_t* pui32Inputs, const uint32_t* pui32Resources,
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

