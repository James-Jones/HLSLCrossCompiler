#include "internal_includes/tokens.h"
#include "internal_includes/structs.h"
#include "internal_includes/decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"
#include "internal_includes/toGLSLInstruction.h"
#include "internal_includes/toGLSLOperand.h"
#include "internal_includes/toGLSLDeclaration.h"
#include "internal_includes/languages.h"
#include "internal_includes/debug.h"
#include "internal_includes/controlFlowGraph.h"

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

static void ClearDependencyData(SHADER_TYPE eType, GLSLCrossDependencyData* depends)
{
    if(depends == NULL)
    {
        return;
    }

    switch(eType)
    {
        case PIXEL_SHADER:
        {
            uint32_t i;
            for(i=0;i<MAX_SHADER_VEC4_INPUT; ++i)
            {
                depends->aePixelInputInterpolation[i] = INTERPOLATION_UNDEFINED;
            }
            break;
        }
        case HULL_SHADER:
        {
            depends->eTessPartitioning = TESSELLATOR_PARTITIONING_UNDEFINED;
            depends->eTessOutPrim = TESSELLATOR_OUTPUT_UNDEFINED;
            break;
        }
    }
}

void AddIndentation(HLSLCrossCompilerContext* psContext)
{
    int i;
    int indent = psContext->indent;
    bstring glsl = *psContext->currentGLSLString;
    for(i=0; i < indent; ++i)
    {
        bcatcstr(glsl, "    ");
    }
}

void AddVersionDependentCode(HLSLCrossCompilerContext* psContext)
{
    bstring glsl = *psContext->currentGLSLString;

    if(psContext->psShader->ui32MajorVersion <= 3)
    {
		bcatcstr(glsl, "int RepCounter;\n");
		if(psContext->psShader->eShaderType == VERTEX_SHADER)
		{
			uint32_t texCoord;
			bcatcstr(glsl, "ivec4 Address;\n");

			if(InOutSupported(psContext->psShader->eTargetLanguage))
			{
				bcatcstr(glsl, "out vec4 OffsetColour;\n");
				bcatcstr(glsl, "out vec4 BaseColour;\n");

				bcatcstr(glsl, "out vec4 Fog;\n");

				for(texCoord=0; texCoord<8; ++texCoord)
				{
					bformata(glsl, "out vec4 TexCoord%d;\n", texCoord);
				}
			}
			else
			{
				bcatcstr(glsl, "varying vec4 OffsetColour;\n");
				bcatcstr(glsl, "varying vec4 BaseColour;\n");

				bcatcstr(glsl, "varying vec4 Fog;\n");

				for(texCoord=0; texCoord<8; ++texCoord)
				{
					bformata(glsl, "varying vec4 TexCoord%d;\n", texCoord);
				}
			}
		}
		else
		{
			uint32_t renderTargets, texCoord;

			bcatcstr(glsl, "varying vec4 OffsetColour;\n");
			bcatcstr(glsl, "varying vec4 BaseColour;\n");

			bcatcstr(glsl, "varying vec4 Fog;\n");

			for(texCoord=0; texCoord<8; ++texCoord)
			{
				bformata(glsl, "varying vec4 TexCoord%d;\n", texCoord);
			}

			for(renderTargets=0; renderTargets<8; ++renderTargets)
			{
				bformata(glsl, "#define Output%d gl_FragData[%d]\n", renderTargets, renderTargets);
			}
		}
    }

	if(!HaveCompute(psContext->psShader->eTargetLanguage))
	{
		if(psContext->psShader->eShaderType == COMPUTE_SHADER)
		{
			bcatcstr(glsl,"#extension GL_ARB_compute_shader : enable\n");
			bcatcstr(glsl,"#extension GL_ARB_shader_storage_buffer_object : enable\n");
		}
	}

	if (!HaveAtomicMem(psContext->psShader->eTargetLanguage) ||
		!HaveAtomicCounter(psContext->psShader->eTargetLanguage))
	{
		if( psContext->psShader->aiOpcodeUsed[OPCODE_IMM_ATOMIC_ALLOC] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_IMM_ATOMIC_CONSUME] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_DCL_UNORDERED_ACCESS_VIEW_STRUCTURED])
		{
			bcatcstr(glsl,"#extension GL_ARB_shader_atomic_counters : enable\n");

			bcatcstr(glsl,"#extension GL_ARB_shader_storage_buffer_object : enable\n");
		}
	}

	if(!HaveGather(psContext->psShader->eTargetLanguage))
	{
		if(psContext->psShader->aiOpcodeUsed[OPCODE_GATHER4] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_GATHER4_PO_C] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_GATHER4_PO] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_GATHER4_C])
		{
			bcatcstr(glsl,"#extension GL_ARB_texture_gather : enable\n");
		}
	}

	if(!HaveGatherNonConstOffset(psContext->psShader->eTargetLanguage))
	{
		if(psContext->psShader->aiOpcodeUsed[OPCODE_GATHER4_PO_C] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_GATHER4_PO])
		{
			bcatcstr(glsl,"#extension GL_ARB_gpu_shader5 : enable\n");
		}
	}

	if(!HaveQueryLod(psContext->psShader->eTargetLanguage))
	{
		if(psContext->psShader->aiOpcodeUsed[OPCODE_LOD])
		{
			bcatcstr(glsl,"#extension GL_ARB_texture_query_lod : enable\n");
		}
	}

	if(!HaveQueryLevels(psContext->psShader->eTargetLanguage))
	{
		if(psContext->psShader->aiOpcodeUsed[OPCODE_RESINFO])
		{
			bcatcstr(glsl,"#extension GL_ARB_texture_query_levels : enable\n");
		}
	}

	if(!HaveImageLoadStore(psContext->psShader->eTargetLanguage))
	{
		if(psContext->psShader->aiOpcodeUsed[OPCODE_STORE_UAV_TYPED] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_STORE_RAW] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_STORE_STRUCTURED])
		{
			bcatcstr(glsl,"#extension GL_ARB_shader_image_load_store : enable\n");
			bcatcstr(glsl,"#extension GL_ARB_shader_bit_encoding : enable\n");
		}
		else
		if(psContext->psShader->aiOpcodeUsed[OPCODE_LD_UAV_TYPED] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_LD_RAW] ||
			psContext->psShader->aiOpcodeUsed[OPCODE_LD_STRUCTURED])
		{
			bcatcstr(glsl,"#extension GL_ARB_shader_image_load_store : enable\n");
		}
	}
	

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

	if(HaveUVec(psContext->psShader->eTargetLanguage))
	{
		bcatcstr(glsl,"struct uvec1 {\n");
		bcatcstr(glsl,"\tuint x;\n");
		bcatcstr(glsl,"};\n");
	}

    bcatcstr(glsl,"struct ivec1 {\n");
    bcatcstr(glsl,"\tint x;\n");
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

    if(SubroutinesSupported(psContext->psShader->eTargetLanguage))
    {
        bcatcstr(glsl, "subroutine void SubroutineType();\n");
    }
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
        case LANG_440:
        {
            return "#version 440\n";
            break;
        }
        default:
        {
            return "";
            break;
        }
    }
}

void TranslateToGLSL(HLSLCrossCompilerContext* psContext, GLLang* planguage)
{
    bstring glsl;
    uint32_t i;
    Shader* psShader = psContext->psShader;
    GLLang language = *planguage;
    const uint32_t ui32InstCount = psShader->ui32InstCount;
    const uint32_t ui32DeclCount = psShader->ui32DeclCount;

    psContext->indent = 0;

    if(language == LANG_DEFAULT)
    {
        language = ChooseLanguage(psShader);
        *planguage = language;
    }

    glsl = bfromcstralloc (1024, GetVersionString(language));

    psContext->glsl = glsl;
	psContext->earlyMain = bfromcstralloc (1024, "");
    for(i=0; i<NUM_PHASES;++i)
    {
        psContext->postShaderCode[i] = bfromcstralloc (1024, "");
    }
    psContext->currentGLSLString = &glsl;
    psShader->eTargetLanguage = language;
    psContext->currentPhase = MAIN_PHASE;

    ClearDependencyData(psShader->eShaderType, psContext->psDependencies);

    AddVersionDependentCode(psContext);

    if(psContext->flags & HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT)
    {
        bcatcstr(glsl, "layout(std140) uniform;\n");
    }

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

        //control
        psContext->currentPhase = HS_CTRL_POINT_PHASE;

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
			SetDataTypes(psContext, psShader->psHSControlPointPhaseInstr, psShader->ui32HSControlPointInstrCount);

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
        psContext->currentPhase = HS_FORK_PHASE;
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

			SetDataTypes(psContext, psShader->apsHSForkPhaseInstr[forkIndex], psShader->aui32HSForkInstrCount[forkIndex]-1);

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

                    if(psContext->havePostShaderCode[psContext->currentPhase])
                    {
#ifdef _DEBUG
                        AddIndentation(psContext);
                        bcatcstr(glsl, "//--- Post shader code ---\n");
#endif
                        bconcat(glsl, psContext->postShaderCode[psContext->currentPhase]);
#ifdef _DEBUG
                        AddIndentation(psContext);
                        bcatcstr(glsl, "//--- End post shader code ---\n");
#endif
                    }
                }

            psContext->indent--;
            bcatcstr(glsl, "}\n");
        }


        //join
        psContext->currentPhase = HS_JOIN_PHASE;
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
			SetDataTypes(psContext, psShader->psHSJoinPhaseInstr, psShader->ui32HSJoinInstrCount);

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

#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//--- Start Early Main ---\n");
#endif
            bconcat(glsl, psContext->earlyMain);
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//--- End Early Main ---\n");
#endif

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

        if(psContext->psDependencies)
        {
            //Save partitioning and primitive type for use by domain shader.
            psContext->psDependencies->eTessOutPrim = psShader->sInfo.eTessOutPrim;

            psContext->psDependencies->eTessPartitioning = psShader->sInfo.eTessPartitioning;
        }

        return;
    }

    if(psShader->eShaderType == DOMAIN_SHADER && psContext->psDependencies)
    {
        //Load partitioning and primitive type from hull shader.
        switch(psContext->psDependencies->eTessOutPrim)
        {
            case TESSELLATOR_OUTPUT_TRIANGLE_CW:
            {
                bcatcstr(glsl, "layout(cw) in;\n");
                break;
            }
            case TESSELLATOR_OUTPUT_POINT:
            {
                bcatcstr(glsl, "layout(point_mode) in;\n");
                break;
            }
            default:
            {
                break;
            }
        }

        switch(psContext->psDependencies->eTessPartitioning)
        {
            case TESSELLATOR_PARTITIONING_FRACTIONAL_ODD:
            {
                bcatcstr(glsl, "layout(fractional_odd_spacing) in;\n");
                break;
            }
            case TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN:
            {
                bcatcstr(glsl, "layout(fractional_even_spacing) in;\n");
                break;
            }
            default:
            {
                break;
            }
        }
    }

    for(i=0; i < ui32DeclCount; ++i)
    {
        TranslateDeclaration(psContext, psShader->psDecl+i);
    }

    bcatcstr(glsl, "void main()\n{\n");

    psContext->indent++;

#ifdef _DEBUG
    AddIndentation(psContext);
    bcatcstr(glsl, "//--- Start Early Main ---\n");
#endif
	bconcat(glsl, psContext->earlyMain);
#ifdef _DEBUG
    AddIndentation(psContext);
    bcatcstr(glsl, "//--- End Early Main ---\n");
#endif

    MarkIntegerImmediates(psContext);

	SetDataTypes(psContext, psShader->psInst, ui32InstCount);

	CFGBuildGraph(psContext->psCFG, psShader->psInst, ui32InstCount);

#ifdef _DEBUG
	CFGVisualiseGraph(psContext->psCFG);
#endif

    for(i=0; i < ui32InstCount; ++i)
    {
        TranslateInstruction(psContext, psShader->psInst+i);
    }

    psContext->indent--;

    bcatcstr(glsl, "}\n");
}

static void FreeSubOperands(Instruction* psInst, const uint32_t ui32NumInsts)
{
	uint32_t ui32Inst;
	for(ui32Inst = 0; ui32Inst < ui32NumInsts; ++ui32Inst)
	{
		Instruction* psCurrentInst = &psInst[ui32Inst];
		const uint32_t ui32NumOperands = psCurrentInst->ui32NumOperands;
		uint32_t ui32Operand;

		for(ui32Operand = 0; ui32Operand < ui32NumOperands; ++ui32Operand)
		{
			uint32_t ui32SubOperand;
			for(ui32SubOperand = 0; ui32SubOperand < MAX_SUB_OPERANDS; ++ui32SubOperand)
			{
				if(psCurrentInst->asOperands[ui32Operand].psSubOperand[ui32SubOperand])
				{
					free(psCurrentInst->asOperands[ui32Operand].psSubOperand[ui32SubOperand]);
					psCurrentInst->asOperands[ui32Operand].psSubOperand[ui32SubOperand] = NULL;
				}
			}
		}
	}
}

HLSLCC_API int HLSLCC_APIENTRY TranslateHLSLFromMem(const char* shader,
    unsigned int flags,
    GLLang language,
    GLSLCrossDependencyData* dependencies,
    GLSLShader* result)
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
        sContext.psDependencies = dependencies;
		sContext.psCFG = malloc(sizeof(ControlFlowGraph));

        for(i=0; i<NUM_PHASES;++i)
        {
            sContext.havePostShaderCode[i] = 0;
        }

        TranslateToGLSL(&sContext, &language);

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
        for(i=0; i<NUM_PHASES; ++i)
        {
            bdestroy(sContext.postShaderCode[i]);
        }

        free(psShader->psHSControlPointPhaseDecl);
		FreeSubOperands(psShader->psHSControlPointPhaseInstr, psShader->ui32HSControlPointInstrCount);
        free(psShader->psHSControlPointPhaseInstr);

        for(i=0; i < psShader->ui32ForkPhaseCount; ++i)
        {
            free(psShader->apsHSForkPhaseDecl[i]);
			FreeSubOperands(psShader->apsHSForkPhaseInstr[i], psShader->aui32HSForkInstrCount[i]);
            free(psShader->apsHSForkPhaseInstr[i]);
        }
        free(psShader->psHSJoinPhaseDecl);
		FreeSubOperands(psShader->psHSJoinPhaseInstr, psShader->ui32HSJoinInstrCount);
        free(psShader->psHSJoinPhaseInstr);

        free(psShader->psDecl);
		FreeSubOperands(psShader->psInst, psShader->ui32InstCount);
        free(psShader->psInst);
        
        result->reflection = psShader->sInfo;

        free(psShader);

		CFGFreeGraph(sContext.psCFG);
		free(sContext.psCFG);

		success = 1;
    }

    shader = 0;
    tokens = 0;

    /* Fill in the result struct */

    result->shaderType = GLSLShaderType;
    result->sourceCode = glslcstr;
    result->GLSLLanguage = language;

	return success;
}

HLSLCC_API int HLSLCC_APIENTRY TranslateHLSLFromFile(const char* filename,
    unsigned int flags,
    GLLang language,
    GLSLCrossDependencyData* dependencies,
    GLSLShader* result)
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

    success = TranslateHLSLFromMem(shader, flags, language, dependencies, result);

    free(shader);

    return success;
}

HLSLCC_API void HLSLCC_APIENTRY FreeGLSLShader(GLSLShader* s)
{
    bcstrfree(s->sourceCode);
    s->sourceCode = NULL;
    FreeShaderInfo(&s->reflection);
}

