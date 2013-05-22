#ifndef HLSLCC_H_
#define HLSLCC_H_

#if defined (_WIN32) && defined(HLSLCC_DYNLIB)
    #define HLSLCC_APIENTRY __stdcall
    #if defined(libHLSLcc_EXPORTS)
        #define HLSLCC_API __declspec(dllexport)
    #else
        #define HLSLCC_API __declspec(dllimport)
    #endif
#else
    #define HLSLCC_APIENTRY
    #define HLSLCC_API
#endif

#include "pstdint.h"

typedef enum
{
    LANG_DEFAULT,// Depends on the HLSL shader model.
    LANG_ES_100,
    LANG_ES_300,
    LANG_120,
    LANG_130,
    LANG_140,
    LANG_150,
    LANG_330,
    LANG_400,
    LANG_410,
    LANG_420,
    LANG_430
} GLLang;

static enum {MAX_SHADER_VEC4_OUTPUT = 512};
static enum {MAX_SHADER_VEC4_INPUT = 512};
static enum {MAX_TEXTURES = 128};
static enum {MAX_FORK_PHASES = 2};
static enum {MAX_FUNCTION_BODIES = 1024};
static enum {MAX_CLASS_TYPES = 1024};
static enum {MAX_FUNCTION_POINTERS = 128};

//Reflection
#define MAX_REFLECT_STRING_LENGTH 512
#define MAX_SHADER_VARS 256
#define MAX_CBUFFERS 256
#define MAX_UAV 256
#define MAX_FUNCTION_TABLES 256

typedef enum SPECIAL_NAME
{
    NAME_UNDEFINED = 0,
    NAME_POSITION = 1,
    NAME_CLIP_DISTANCE = 2,
    NAME_CULL_DISTANCE = 3,
    NAME_RENDER_TARGET_ARRAY_INDEX = 4,
    NAME_VIEWPORT_ARRAY_INDEX = 5,
    NAME_VERTEX_ID = 6,
    NAME_PRIMITIVE_ID = 7,
    NAME_INSTANCE_ID = 8,
    NAME_IS_FRONT_FACE = 9,
    NAME_SAMPLE_INDEX = 10,
    // The following are added for D3D11
    NAME_FINAL_QUAD_U_EQ_0_EDGE_TESSFACTOR = 11, 
    NAME_FINAL_QUAD_V_EQ_0_EDGE_TESSFACTOR = 12, 
    NAME_FINAL_QUAD_U_EQ_1_EDGE_TESSFACTOR = 13, 
    NAME_FINAL_QUAD_V_EQ_1_EDGE_TESSFACTOR = 14, 
    NAME_FINAL_QUAD_U_INSIDE_TESSFACTOR = 15, 
    NAME_FINAL_QUAD_V_INSIDE_TESSFACTOR = 16, 
    NAME_FINAL_TRI_U_EQ_0_EDGE_TESSFACTOR = 17, 
    NAME_FINAL_TRI_V_EQ_0_EDGE_TESSFACTOR = 18, 
    NAME_FINAL_TRI_W_EQ_0_EDGE_TESSFACTOR = 19, 
    NAME_FINAL_TRI_INSIDE_TESSFACTOR = 20, 
    NAME_FINAL_LINE_DETAIL_TESSFACTOR = 21,
    NAME_FINAL_LINE_DENSITY_TESSFACTOR = 22,
} SPECIAL_NAME;


typedef enum { 
  INOUT_COMPONENT_UNKNOWN  = 0,
  INOUT_COMPONENT_UINT32   = 1,
  INOUT_COMPONENT_SINT32   = 2,
  INOUT_COMPONENT_FLOAT32  = 3
} INOUT_COMPONENT_TYPE;

typedef struct InOutSignature_TAG
{
    char SemanticName[MAX_REFLECT_STRING_LENGTH];
    uint32_t ui32SemanticIndex;
    SPECIAL_NAME eSystemValueType;
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

typedef enum REFLECT_RESOURCE_DIMENSION
{
    REFLECT_RESOURCE_DIMENSION_UNKNOWN = 0,
    REFLECT_RESOURCE_DIMENSION_BUFFER = 1,
    REFLECT_RESOURCE_DIMENSION_TEXTURE1D = 2,
    REFLECT_RESOURCE_DIMENSION_TEXTURE1DARRAY = 3,
    REFLECT_RESOURCE_DIMENSION_TEXTURE2D = 4,
    REFLECT_RESOURCE_DIMENSION_TEXTURE2DARRAY = 5,
    REFLECT_RESOURCE_DIMENSION_TEXTURE2DMS = 6,
    REFLECT_RESOURCE_DIMENSION_TEXTURE2DMSARRAY = 7,
    REFLECT_RESOURCE_DIMENSION_TEXTURE3D = 8,
    REFLECT_RESOURCE_DIMENSION_TEXTURECUBE = 9,
    REFLECT_RESOURCE_DIMENSION_TEXTURECUBEARRAY = 10,
    REFLECT_RESOURCE_DIMENSION_RAW_BUFFER = 11,
    REFLECT_RESOURCE_DIMENSION_STRUCTURED_BUFFER = 12,
} REFLECT_RESOURCE_DIMENSION;

typedef struct ResourceBinding_TAG
{
    char Name[MAX_REFLECT_STRING_LENGTH];
    ResourceType eType;
    uint32_t ui32BindPoint;
    uint32_t ui32BindCount;
    uint32_t ui32Flags;
    REFLECT_RESOURCE_DIMENSION eDimension;
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

typedef enum TESSELLATOR_PARTITIONING
{
    TESSELLATOR_PARTITIONING_UNDEFINED       = 0,
    TESSELLATOR_PARTITIONING_INTEGER         = 1,
    TESSELLATOR_PARTITIONING_POW2            = 2,
    TESSELLATOR_PARTITIONING_FRACTIONAL_ODD  = 3,
    TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN = 4
} TESSELLATOR_PARTITIONING;

typedef enum TESSELLATOR_OUTPUT_PRIMITIVE
{
    TESSELLATOR_OUTPUT_UNDEFINED     = 0,
    TESSELLATOR_OUTPUT_POINT         = 1,
    TESSELLATOR_OUTPUT_LINE          = 2,
    TESSELLATOR_OUTPUT_TRIANGLE_CW   = 3,
    TESSELLATOR_OUTPUT_TRIANGLE_CCW  = 4
} TESSELLATOR_OUTPUT_PRIMITIVE;

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
    uint32_t aui32UAVBindpointRemap[MAX_UAV];

    TESSELLATOR_PARTITIONING eTessPartitioning;
    TESSELLATOR_OUTPUT_PRIMITIVE eTessOutPrim;
} ShaderInfo;

typedef enum INTERPOLATION_MODE
{
    INTERPOLATION_UNDEFINED = 0,
    INTERPOLATION_CONSTANT = 1,
    INTERPOLATION_LINEAR = 2,
    INTERPOLATION_LINEAR_CENTROID = 3,
    INTERPOLATION_LINEAR_NOPERSPECTIVE = 4,
    INTERPOLATION_LINEAR_NOPERSPECTIVE_CENTROID = 5,
    INTERPOLATION_LINEAR_SAMPLE = 6,
    INTERPOLATION_LINEAR_NOPERSPECTIVE_SAMPLE = 7,
} INTERPOLATION_MODE;

//The shader stages (Vertex, Pixel et al) do not depend on each other
//in HLSL. GLSL is a different story. HLSLCrossCompiler requires
//that hull shaders must be compiled before domain shaders, and
//the pixel shader must be compiled before all of the others.
//Durring compiliation the GLSLCrossDependencyData struct will
//carry over any information needed about a different shader stage
//in order to construct valid GLSL shader combinations.

//Using GLSLCrossDependencyData is optional. However some shader
//combinations may show link failures, or runtime errors.
typedef struct
{
    //dcl_tessellator_partitioning and dcl_tessellator_output_primitive appear in hull shader for D3D,
    //but they appear on inputs inside domain shaders for GL.
    //Hull shader must be compiled before domain so the
    //ensure correct partitioning and primitive type information
    //can be saved when compiling hull and passed to domain compiliation.
    TESSELLATOR_PARTITIONING eTessPartitioning;
    TESSELLATOR_OUTPUT_PRIMITIVE eTessOutPrim;

    //Required if PixelInterpDependency is true
    INTERPOLATION_MODE aePixelInputInterpolation[MAX_SHADER_VEC4_INPUT];
} GLSLCrossDependencyData;

typedef struct
{
    int shaderType; //One of the GL enums.
    char* sourceCode;
    ShaderInfo reflection;
    GLLang GLSLLanguage;
} GLSLShader;

/*HLSL constant buffers are treated as default-block unform arrays by default. This is done
  to support versions of GLSL which lack ARB_uniform_buffer_object functionality.
  Setting this flag causes each one to have its own uniform block.
  Note: Currently the nth const buffer will be named UnformBufferN. This is likey to change to the original HLSL name in the future.*/
static const unsigned int HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT = 0x1;

static const unsigned int HLSLCC_FLAG_ORIGIN_UPPER_LEFT = 0x2;

static const unsigned int HLSLCC_FLAG_PIXEL_CENTER_INTEGER = 0x4;

static const unsigned int HLSLCC_FLAG_GLOBAL_CONSTS_NEVER_IN_UBO = 0x8;

//GS enabled?
//Affects vertex shader (i.e. need to compile vertex shader again to use with/without GS).
//This flag is needed in order for the interfaces between stages to match when GS is in use.
//PS inputs VtxGeoOutput
//GS outputs VtxGeoOutput
//Vs outputs VtxOutput if GS enabled. VtxGeoOutput otherwise.
static const unsigned int HLSLCC_FLAG_GS_ENABLED = 0x10;

static const unsigned int HLSLCC_FLAG_TESS_ENABLED = 0x20;

//Either use this flag or glBindFragDataLocationIndexed.
//When set the first pixel shader output is the first input to blend
//equation, the others go to the second input.
static const unsigned int HLSLCC_DUAL_SOURCE_BLENDING = 0x40;

HLSLCC_API int HLSLCC_APIENTRY TranslateHLSLFromFile(const char* filename,
                                                     unsigned int flags,
                                                     GLLang language,
                                                     GLSLCrossDependencyData* dependencies,
                                                     GLSLShader* result);

HLSLCC_API int HLSLCC_APIENTRY TranslateHLSLFromMem(const char* shader,
                                                    unsigned int flags,
                                                    GLLang language,
                                                    GLSLCrossDependencyData* dependencies,
                                                    GLSLShader* result);

HLSLCC_API void HLSLCC_APIENTRY FreeGLSLShader(GLSLShader*);

#endif

