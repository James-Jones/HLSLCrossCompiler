#ifndef TO_GLSL_H
#define TO_GLSL_H

#include "languages.h"
#include "reflect.h"

//Current tasks:
//Support rendezvous by API resource use-case (GL_ARB_separate_shader_objects). Requires location qualifiers and possibly other changes.
//Maybe use structs for constant buffers.
//Further work on default values for constants.
//Improve type/swizzle checking to allow hlsl_opcode_funcs to be removed.
//Use real integer types (ivec*) where appropriate.
//Improving support for integer immediates on MOV instructions by checking if next usage is with an integer opcode.

typedef struct
{
    int shaderType; //One of the GL enums.
    char* sourceCode;
    ShaderInfo reflection;
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

int TranslateHLSLFromFile(const char* filename, unsigned int flags, GLLang language, GLSLShader* result);
int TranslateHLSLFromMem(const char* shader, unsigned int flags, GLLang language, GLSLShader* result);

void FreeGLSLShader(GLSLShader*);

#endif
