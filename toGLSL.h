#ifndef TO_GLSL_H
#define TO_GLSL_H

#include "languages.h"
#include "reflect.h"
#include "shaderLimits.h"

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
    //Hull shader must be compiled before domain in order
    //to ensure correct partitioning and primitive type information
    //is OR'ed into mCompileFlags.
    TESSELLATOR_PARTITIONING eTessOutPrim;
    TESSELLATOR_OUTPUT_PRIMITIVE eTessPartitioning;

    //Required if PixelInpterpDependency is true
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

//dcl_tessellator_partitioning and dcl_tessellator_output_primitive appear in hull shader for D3D,
//but they appear on inputs inside domain shaders for GL.
//Use HLSLCC_FLAGS to set the paritioning and primitive type. The correct values to use
//can be extracted from the hull shader reflection information.
static const unsigned int HLSLCC_FLAG_FRACTIONAL_EVEN_SPACING = 0x40;//EQUAL_SPACING is default
static const unsigned int HLSLCC_FLAG_FRACTIONAL_ODD_SPACING = 0x80;
static const unsigned int HLSLCC_FLAG_CW = 0x100; //CCW is default.
static const unsigned int HLSLCC_FLAG_TESS_POINT_MODE = 0x200;

//Either use this flag or glBindFragDataLocationIndexed.
//When set the first pixel shader output is the first input to blend
//equation, the others go to the second input.
static const unsigned int HLSLCC_DUAL_SOURCE_BLENDING = 0x400;

int TranslateHLSLFromFile(const char* filename, unsigned int flags, GLLang language, GLSLCrossDependencyData* dependencies, GLSLShader* result);
int TranslateHLSLFromMem(const char* shader, unsigned int flags, GLLang language, GLSLCrossDependencyData* dependencies, GLSLShader* result);

void FreeGLSLShader(GLSLShader*);

#endif
