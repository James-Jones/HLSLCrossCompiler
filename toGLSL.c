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
#include "debug.h"

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

	//Enable conservative depth if the extension is defined by the GLSL compiler.
	bcatcstr(glsl,"#ifdef GL_ARB_conservative_depth\n\t#extension GL_ARB_conservative_depth : enable\n#endif\n");

    if((psContext->flags & HLSLCC_FLAG_ORIGIN_UPPER_LEFT)
        && (psContext->psShader->eTargetLanguage >= LANG_150))
    {
        bcatcstr(glsl,"layout(origin_upper_left) in vec4 gl_FragCoord;\n");
    }

    if((psContext->flags & HLSLCC_FLAG_PIXEL_CENTER_INTEGER)
        && (psContext->psShader->eTargetLanguage >= LANG_150))
    {
        bcatcstr(glsl,"layout(pixel_center_integer) in vec4 gl_FragCoord;\n");
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
    if(psContext->psShader->eShaderType == VERTEX_SHADER && psContext->psShader->eTargetLanguage >= LANG_410)
    {
        bcatcstr(glsl, "out gl_PerVertex {\n");
        bcatcstr(glsl, "vec4 gl_Position;\n");
        bcatcstr(glsl, "float gl_PointSize;\n");
        bcatcstr(glsl, "float gl_ClipDistance[];");
        bcatcstr(glsl, "};\n");
    }

    /* Texture functions have overloaded parameters */
    if(HaveOverloadedTextureFuncs(psContext->psShader->eTargetLanguage))
    {
        bcatcstr(glsl, "#define shadow2DLod textureLod\n");
        bcatcstr(glsl, "#define shadow1DLod textureLod\n");
        bcatcstr(glsl, "#define shadow2D texture\n");
        bcatcstr(glsl, "#define shadow1D texture\n");
        bcatcstr(glsl, "#define texture3DLod textureLod\n");
        bcatcstr(glsl, "#define texture2DLod textureLod\n");
        bcatcstr(glsl, "#define texture1DLod textureLod\n");
        bcatcstr(glsl, "#define textureCubeLod textureLod\n");
        bcatcstr(glsl, "#define texture3D texture\n");
        bcatcstr(glsl, "#define texture2D texture\n");
        bcatcstr(glsl, "#define texture1D texture\n");
        bcatcstr(glsl, "#define textureCube texture\n");
    }

    //The fragment language has no default precision qualifier for floating point types.
    if(psContext->psShader->eShaderType == PIXEL_SHADER &&
        psContext->psShader->eTargetLanguage == LANG_ES_100 || psContext->psShader->eTargetLanguage == LANG_ES_300 )
    {
        bcatcstr(glsl,"precision highp float;\n");
    }

    /* There is no default precision qualifier for the following sampler types in either the vertex or fragment language: */
    if(psContext->psShader->eTargetLanguage == LANG_ES_300 )
    {
        bcatcstr(glsl,"precision lowp sampler3D;\n");
        bcatcstr(glsl,"precision lowp samplerCubeShadow;\n");
        bcatcstr(glsl,"precision lowp sampler2DShadow;\n");
        bcatcstr(glsl,"precision lowp sampler2DArray;\n");
        bcatcstr(glsl,"precision lowp sampler2DArrayShadow;\n");
        bcatcstr(glsl,"precision lowp isampler2D;\n");
        bcatcstr(glsl,"precision lowp isampler3D;\n");
        bcatcstr(glsl,"precision lowp isamplerCube;\n");
        bcatcstr(glsl,"precision lowp isampler2DArray;\n");
        bcatcstr(glsl,"precision lowp usampler2D;\n");
        bcatcstr(glsl,"precision lowp usampler3D;\n");
        bcatcstr(glsl,"precision lowp usamplerCube;\n");
        bcatcstr(glsl,"precision lowp usampler2DArray;\n");
    }
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
	psContext->earlyMain = bfromcstralloc (1024, "");
    psShader->eTargetLanguage = language;

    AddVersionDependentCode(psContext);

    //Special case. Can have multiple phases.
    if(psShader->eShaderType == HULL_SHADER)
    {
        int haveInstancedForkPhase = 0;
        uint32_t forkIndex = 0;

        ConsolidateHullTempVars(psShader);

        for(i=0; i < psShader->ui32HSDeclCount; ++i)
        {
            TranslateDeclaration(psContext, psShader->psHSDecl+i);
        }

        AddOpcodeFuncs(psContext);

        //control
        if(psShader->ui32HSControlPointDeclCount)
        {
            bcatcstr(glsl, "//Control point phase declarations\n");
            for(i=0; i < psShader->ui32HSControlPointDeclCount; ++i)
            {
                TranslateDeclaration(psContext, psShader->psHSControlPointPhaseDecl+i);
            }
        }

        if(psShader->ui32HSControlPointInstrCount)
        {
            bcatcstr(glsl, "void control_point_phase()\n{\n");
            psContext->indent++;
                for(i=0; i < psShader->ui32HSControlPointInstrCount; ++i)
                {
                    TranslateInstruction(psContext, psShader->psHSControlPointPhaseInstr+i);
                }
            psContext->indent--;
            bcatcstr(glsl, "}\n");
        }

        //fork
        for(forkIndex = 0; forkIndex < psShader->ui32ForkPhaseCount; ++forkIndex)
        {
            bcatcstr(glsl, "//Fork phase declarations\n");
            for(i=0; i < psShader->aui32HSForkDeclCount[forkIndex]; ++i)
            {
                TranslateDeclaration(psContext, psShader->apsHSForkPhaseDecl[forkIndex]+i);
                if(psShader->apsHSForkPhaseDecl[forkIndex][i].eOpcode == OPCODE_DCL_HS_FORK_PHASE_INSTANCE_COUNT)
                {
                    haveInstancedForkPhase = 1;
                }
            }

            bformata(glsl, "void fork_phase%d()\n{\n", forkIndex);
            psContext->indent++;

                if(haveInstancedForkPhase)
                {
                    AddIndentation(psContext);
                    bformata(glsl, "for(int forkInstanceID = 0; forkInstanceID < HullPhase%dInstanceCount; ++forkInstanceID) {\n", forkIndex);
                    psContext->indent++;
                }

                    //The minus one here is remove the return statement at end of phases.
                    //This is needed otherwise the for loop will only run once.
                    ASSERT(psShader->apsHSForkPhaseInstr[forkIndex][psShader->aui32HSForkInstrCount[forkIndex]-1].eOpcode == OPCODE_RET);
                    for(i=0; i < psShader->aui32HSForkInstrCount[forkIndex]-1; ++i)
                    {
                        TranslateInstruction(psContext, psShader->apsHSForkPhaseInstr[forkIndex]+i);
                    }

                if(haveInstancedForkPhase)
                {
                    psContext->indent--;
                    AddIndentation(psContext);
                    bcatcstr(glsl, "}\n");
                }

            psContext->indent--;
            bcatcstr(glsl, "}\n");
        }


        //join
        if(psShader->ui32HSJoinDeclCount)
        {
            bcatcstr(glsl, "//Join phase declarations\n");
            for(i=0; i < psShader->ui32HSJoinDeclCount; ++i)
            {
                TranslateDeclaration(psContext, psShader->psHSJoinPhaseDecl+i);
            }
        }

        if(psShader->ui32HSJoinInstrCount)
        {
            bcatcstr(glsl, "void join_phase()\n{\n");
            psContext->indent++;

                for(i=0; i < psShader->ui32HSJoinInstrCount; ++i)
                {
                    TranslateInstruction(psContext, psShader->psHSJoinPhaseInstr+i);
                }

            psContext->indent--;
            bcatcstr(glsl, "}\n");
        }

        bcatcstr(glsl, "void main()\n{\n");

            psContext->indent++;

            if(psShader->ui32HSControlPointInstrCount)
            {
                AddIndentation(psContext);
                bcatcstr(glsl, "control_point_phase();\n");

                if(psShader->ui32ForkPhaseCount || psShader->ui32HSJoinInstrCount)
                {
                    AddIndentation(psContext);
                    bcatcstr(glsl, "barrier();\n");
                }
            }
            for(forkIndex = 0; forkIndex < psShader->ui32ForkPhaseCount; ++forkIndex)
            {
                AddIndentation(psContext);
                bformata(glsl, "fork_phase%d();\n", forkIndex);

                if(psShader->ui32HSJoinInstrCount || (forkIndex+1 < psShader->ui32ForkPhaseCount))
                {
                    AddIndentation(psContext);
                    bcatcstr(glsl, "barrier();\n");
                }
            }
            if(psShader->ui32HSJoinInstrCount)
            {
                AddIndentation(psContext);
                bcatcstr(glsl, "join_phase();\n");
            }

            psContext->indent--;

        bcatcstr(glsl, "}\n");
        return;
    }

    if(psShader->eShaderType == DOMAIN_SHADER)
    {
        if(psContext->flags & HLSLCC_FLAG_FRACTIONAL_ODD_SPACING)
        {
            bcatcstr(glsl, "layout(fractional_odd_spacing) in;\n");
        }
        if(psContext->flags & HLSLCC_FLAG_FRACTIONAL_EVEN_SPACING)
        {
            bcatcstr(glsl, "layout(fractional_even_spacing) in;\n");
        }
        if(psContext->flags & HLSLCC_FLAG_CW)
        {
            bcatcstr(glsl, "layout(cw) in;\n");
        }
        if(psContext->flags & HLSLCC_FLAG_TESS_POINT_MODE)
        {
            bcatcstr(glsl, "layout(point_mode) in;\n");
        }
    }

    for(i=0; i < ui32DeclCount; ++i)
    {
        TranslateDeclaration(psContext, psShader->psDecl+i);
    }

    AddOpcodeFuncs(psContext);

    bcatcstr(glsl, "void main()\n{\n");

    psContext->indent++;

	bconcat(glsl, psContext->earlyMain);

    for(i=0; i < ui32InstCount; ++i)
    {
        TranslateInstruction(psContext, psShader->psInst+i);
    }

    psContext->indent--;

    bcatcstr(glsl, "}\n");
}

int TranslateHLSLFromMem(const char* shader, unsigned int flags, GLLang language, GLSLShader* result)
{
    uint32_t* tokens;
    Shader* psShader;
    char* glslcstr = NULL;
    int GLSLShaderType = GL_FRAGMENT_SHADER_ARB;
	int success = 0;
    uint32_t i;

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
		bdestroy(sContext.earlyMain);

        free(psShader->psHSControlPointPhaseDecl);
        free(psShader->psHSControlPointPhaseInstr);

        for(i=0; i < psShader->ui32ForkPhaseCount; ++i)
        {
            free(psShader->apsHSForkPhaseDecl[i]);
            free(psShader->apsHSForkPhaseInstr[i]);
        }
        free(psShader->psHSJoinPhaseDecl);
        free(psShader->psHSJoinPhaseInstr);

        free(psShader->psDecl);
        free(psShader->psInst);
        
        result->reflection = psShader->sInfo;

        free(psShader);

		success = 1;
    }

    shader = 0;
    tokens = 0;

    /* Fill in the result struct */

    result->shaderType = GLSLShaderType;
    result->sourceCode = glslcstr;

	return success;
}

int TranslateHLSLFromFile(const char* filename, unsigned int flags, GLLang language, GLSLShader* result)
{
    FILE* shaderFile;
    int length;
    int readLength;
    char* shader;
	int success = 0;

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

    success = TranslateHLSLFromMem(shader, flags, language, result);

    free(shader);

    return success;
}

void FreeGLSLShader(GLSLShader* s)
{
    bcstrfree(s->sourceCode);
    s->sourceCode = NULL;
    FreeShaderInfo(&s->reflection);
}

