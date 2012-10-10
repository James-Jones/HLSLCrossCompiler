#include "tokens.h"
#include "structs.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"
#include "hlsl_opcode_funcs_glsl.h"
#include "toGLSL.h"
#include "toGLSLInstruction.h"
#include "toGLSLOperand.h"
#include "toGLSLDeclaration.h"

#include <assert.h>
#define ASSERT(x) assert(x)

#ifndef GL_VERTEX_SHADER_ARB
#define GL_VERTEX_SHADER_ARB              0x8B31
#endif
#ifndef GL_FRAGMENT_SHADER_ARB
#define GL_FRAGMENT_SHADER_ARB            0x8B30
#endif
#ifndef GL_GEOMETRY_SHADER
#define GL_GEOMETRY_SHADER 0x8DD9
#endif
#ifndef GL_TESS_EVALUATION_SHADER
#define GL_TESS_EVALUATION_SHADER 0x8E87
#endif
#ifndef GL_TESS_CONTROL_SHADER
#define GL_TESS_CONTROL_SHADER 0x8E88
#endif
#ifndef GL_COMPUTE_SHADER
#define GL_COMPUTE_SHADER 0x91B9
#endif

void AddIndentation(HLSLCrossCompilerContext* psContext)
{
    int i;
    int indent = psContext->indent;
    bstring glsl = psContext->glsl;
    for(i=0; i < indent; ++i)
    {
        bcatcstr(glsl, "    ");
    }
}

void AddVersionDependentCode(HLSLCrossCompilerContext* psContext)
{
    bstring glsl = psContext->glsl;

    if(psContext->flags & HLSLCC_FLAG_ORIGIN_UPPER_LEFT)
    {
        bcatcstr(glsl,"#if __VERSION__ >= 150\n layout(origin_upper_left) in vec4 gl_FragCoord; \n#endif\n");
    }

    if(psContext->flags & HLSLCC_FLAG_PIXEL_CENTER_INTEGER)
    {
        bcatcstr(glsl,"#if __VERSION__ >= 150\n layout(pixel_center_integer) in vec4 gl_FragCoord; \n#endif\n");
    }

    /* For versions which do not support a vec1 (currently all versions) */
    bcatcstr(glsl,"struct vec1 {\n");
    bcatcstr(glsl,"\tfloat x;\n");
    bcatcstr(glsl,"};\n");

    /*
        OpenGL 4.1 API spec:
        To use any built-in input or output in the gl_PerVertex block in separable
        program objects, shader code must redeclare that block prior to use.
    */
    if(psContext->psShader->eShaderType == VERTEX_SHADER)
    {
        bcatcstr(glsl, "#if __VERSION__ >= 410\n");
            bcatcstr(glsl, "\tout gl_PerVertex {\n");
            bcatcstr(glsl, "\tvec4 gl_Position;\n");
            bcatcstr(glsl, "\tfloat gl_PointSize;\n");
            bcatcstr(glsl, "\tfloat gl_ClipDistance[];");
            bcatcstr(glsl, "};\n");
        bcatcstr(glsl, "#endif \n");
    }

    /* After GLSL 120 and GLSL ES 100 texture function have overloaded parameters */
    bcatcstr(glsl, "#if __VERSION__ > 120 \n");
        bcatcstr(glsl, "\t#define texture2DLod texture \n");
    bcatcstr(glsl, "#endif \n");
}

void AddOpcodeFuncs(HLSLCrossCompilerContext* psContext)
{
    bstring glsl = psContext->glsl;

    bcatcstr(glsl, "\n");

    bcatcstr(glsl, psz_hlsl_opcode_funcs_glsl);

    bcatcstr(glsl, "\n");
}

GLLang ChooseLanguage(Shader* psShader)
{
    // Depends on the HLSL shader model extracted from bytecode.
    switch(psShader->ui32MajorVersion)
    {
        case 5:
        {
            return LANG_430;
        }
        case 4:
        {
            return LANG_330;
        }
        default:
        {
            return LANG_120;
        }
    }
}

const char* GetVersionString(GLLang language)
{
    switch(language)
    {
        case LANG_ES_100:
        {
            return "#version 100\n";
            break;
        }
        case LANG_ES_300:
        {
            return "#version 300 es\n";
            break;
        }
        case LANG_120:
        {
            return "#version 120\n";
            break;
        }
        case LANG_130:
        {
            return "#version 130\n";
            break;
        }
        case LANG_140:
        {
            return "#version 140\n";
            break;
        }
        case LANG_150:
        {
            return "#version 150\n";
            break;
        }
        case LANG_330:
        {
            return "#version 330\n";
            break;
        }
        case LANG_400:
        {
            return "#version 400\n";
            break;
        }
        case LANG_410:
        {
            return "#version 410\n";
            break;
        }
        case LANG_420:
        {
            return "#version 420\n";
            break;
        }
        case LANG_430:
        {
            return "#version 430\n";
            break;
        }
        default:
        {
            return "";
            break;
        }
    }
}

void TranslateToGLSL(HLSLCrossCompilerContext* psContext, GLLang language)
{
    bstring glsl;
    uint32_t i;
    Shader* psShader = psContext->psShader;
    const uint32_t ui32InstCount = psShader->ui32InstCount;
    const uint32_t ui32DeclCount = psShader->ui32DeclCount;

    psContext->indent = 0;

    if(language == LANG_DEFAULT)
    {
        language = ChooseLanguage(psShader);
    }

    glsl = bfromcstralloc (1024, GetVersionString(language));

    psContext->glsl = glsl;
    psShader->eTargetLanguage = language;

    AddVersionDependentCode(psContext);

    for(i=0; i < ui32DeclCount; ++i)
    {
        TranslateDeclaration(psContext, psShader->psDecl+i);
    }

    AddOpcodeFuncs(psContext);

    bcatcstr(glsl, "void main()\n");
    bcatcstr(glsl, "{\n");

    psContext->indent++;

    for(i=0; i < ui32InstCount; ++i)
    {
        TranslateInstruction(psContext, psShader->psInst+i);
    }

    psContext->indent--;

    bcatcstr(glsl, "}\n");
}

void TranslateHLSLFromMem(const char* shader, unsigned int flags, GLLang language, GLSLShader* result)
{
    uint32_t* tokens;
    Shader* psShader;
    char* glslcstr = NULL;
    int GLSLShaderType = GL_FRAGMENT_SHADER_ARB;

    tokens = (uint32_t*)shader;

    psShader = DecodeDXBC(tokens);

	if(psShader)
    {
        HLSLCrossCompilerContext sContext;

        sContext.psShader = psShader;
        sContext.flags = flags;

        TranslateToGLSL(&sContext, language);

        switch(psShader->eShaderType)
        {
            case VERTEX_SHADER:
            {
                GLSLShaderType = GL_VERTEX_SHADER_ARB;
                break;
            }
            case GEOMETRY_SHADER:
            {
                GLSLShaderType = GL_GEOMETRY_SHADER;
                break;
            }
            case DOMAIN_SHADER:
            {
                GLSLShaderType = GL_TESS_EVALUATION_SHADER;
                break;
            }
            case HULL_SHADER:
            {
                GLSLShaderType = GL_TESS_CONTROL_SHADER;
                break;
            }
            case COMPUTE_SHADER:
            {
                GLSLShaderType = GL_COMPUTE_SHADER;
                break;
            }
            default:
            {
                break;
            }
        }

        glslcstr = bstr2cstr(sContext.glsl, '\0');

        bdestroy(sContext.glsl);

        free(psShader->psDecl);
        free(psShader->psInst);
        free(psShader);
    }

    shader = 0;
    tokens = 0;

    /* Fill in the result struct */

    result->shaderType = GLSLShaderType;
    result->sourceCode = glslcstr;
}

int TranslateHLSLFromFile(const char* filename, unsigned int flags, GLLang language, GLSLShader* result)
{
    FILE* shaderFile;
    int length;
    int readLength;
    char* shader;

    shaderFile = fopen(filename, "rb");

    if(!shaderFile)
    {
        return 0;
    }

    fseek(shaderFile, 0, SEEK_END);
    length = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET);

    shader = (char*)malloc(length+1);

    readLength = fread(shader, 1, length, shaderFile);

    fclose(shaderFile);
    shaderFile = 0;

    shader[readLength] = '\0';

    TranslateHLSLFromMem(shader, flags, language, result);

    free(shader);

    return 1;
}

