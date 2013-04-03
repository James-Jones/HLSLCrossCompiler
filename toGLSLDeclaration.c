#include "toGLSL.h"
#include "toGLSLDeclaration.h"
#include "toGLSLOperand.h"
#include "bstrlib.h"
#include "debug.h"
#include <math.h>

#include <float.h>

#ifdef _MSC_VER
#define isnan(x) _isnan(x)
#define isinf(x) (!_finite(x))
#endif

#define fpcheck(x) (isnan(x) || isinf(x))

extern void AddIndentation(HLSLCrossCompilerContext* psContext);

void TranslateDeclaration(HLSLCrossCompilerContext* psContext, const Declaration* psDecl)
{
    bstring glsl = psContext->glsl;
    Shader* psShader = psContext->psShader;

    switch(psDecl->eOpcode)
    {
        case OPCODE_DCL_INPUT_PS_SGV:
        {
            const SPECIAL_NAME eSpecialName = psDecl->asOperands[0].eSpecialName;
            switch(eSpecialName)
            {
                case NAME_POSITION:
                case NAME_RENDER_TARGET_ARRAY_INDEX:
                case NAME_CLIP_DISTANCE:
                case NAME_VIEWPORT_ARRAY_INDEX:
                case NAME_VERTEX_ID:
                case NAME_PRIMITIVE_ID:
                case NAME_INSTANCE_ID:
                case NAME_IS_FRONT_FACE:
                case NAME_SAMPLE_INDEX:
                {
                    psShader->aSpecialInputs[psDecl->asOperands[0].ui32RegisterNumber] = eSpecialName;
                    break;
                }
                default:
                {
                    bformata(glsl, "in vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " %s\n", psDecl->asOperands[0].pszSpecialName);
                    break;
                }
            }
            break;
        }

        case OPCODE_DCL_OUTPUT_SIV:
        {
            switch(psDecl->asOperands[0].eSpecialName)
            {
                case NAME_POSITION:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_Position\n");
                    break;
                }
                case NAME_RENDER_TARGET_ARRAY_INDEX:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;
					psContext->psShader->abIntegerOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;
                    bcatcstr(glsl, "#define ");
					TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_Layer\n");
                    break;
                }
                case NAME_CLIP_DISTANCE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_ClipDistance\n");
                    break;
                }
                case NAME_VIEWPORT_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_ViewportIndex\n");
                    break;
                }
                case NAME_VERTEX_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_VertexID\n");
                    break;
                }
                case NAME_PRIMITIVE_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_PrimitiveID);\n");
                    break;
                }
                case NAME_INSTANCE_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_InstanceID\n");
                    break;
                }
                case NAME_IS_FRONT_FACE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " gl_FrontFacing\n");
                    break;
                }
		        case NAME_FINAL_QUAD_U_EQ_0_EDGE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;


                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    if(psContext->psShader->aIndexedOutput[psDecl->asOperands[0].ui32RegisterNumber])
                    {
                        bformata(glsl, " gl_TessLevelOuter\n");
                    }
                    else
                    {
                        bformata(glsl, " gl_TessLevelOuter[0]\n");
                    }
                    break;
                }
		        case NAME_FINAL_QUAD_V_EQ_0_EDGE_TESSFACTOR: 
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelOuter[1]\n");
                    break;
                }
		        case NAME_FINAL_QUAD_U_EQ_1_EDGE_TESSFACTOR: 
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0],TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelOuter[2]\n");
                    break;
                }
		        case NAME_FINAL_QUAD_V_EQ_1_EDGE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelOuter[3]\n");
                    break;
                }
		        case NAME_FINAL_TRI_U_EQ_0_EDGE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    if(psContext->psShader->aIndexedOutput[psDecl->asOperands[0].ui32RegisterNumber])
                    {
                        bformata(glsl, " gl_TessLevelOuter\n");
                    }
                    else
                    {
                        bformata(glsl, " gl_TessLevelOuter[0]\n");
                    }
                    break;
                }
		        case NAME_FINAL_TRI_V_EQ_0_EDGE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0],TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelOuter[1]\n");
                    break;
                }
		        case NAME_FINAL_TRI_W_EQ_0_EDGE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelOuter[2]\n");
                    break;
                }
		        case NAME_FINAL_LINE_DENSITY_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    if(psContext->psShader->aIndexedOutput[psDecl->asOperands[0].ui32RegisterNumber])
                    {
                        bformata(glsl, " gl_TessLevelOuter\n");
                    }
                    else
                    {
                        bformata(glsl, " gl_TessLevelOuter[0]\n");
                    }
                    break;
                }
		        case NAME_FINAL_LINE_DETAIL_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelOuter[1]\n");
                    break;
                }
                case NAME_FINAL_TRI_INSIDE_TESSFACTOR:
		        case NAME_FINAL_QUAD_U_INSIDE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    if(psContext->psShader->aIndexedOutput[psDecl->asOperands[0].ui32RegisterNumber])
                    {
                        bformata(glsl, " gl_TessLevelInner\n");
                    }
                    else
                    {
                        bformata(glsl, " gl_TessLevelInner[0]\n");
                    }
                    break;
                }
		        case NAME_FINAL_QUAD_V_INSIDE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                    bcatcstr(glsl, "#undef ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);

                    bcatcstr(glsl, "\n#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NAME_ONLY);
                    bformata(glsl, " gl_TessLevelInner[1]\n");
                    break;
                }
                default:
                {
                    bformata(glsl, "out vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    bformata(glsl, " %s\n", psDecl->asOperands[0].pszSpecialName);
                    break;
                }
            }
            break;
        }
        case OPCODE_DCL_INPUT:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
			//Force the number of components to be 4.
/*dcl_output o3.xy
  dcl_output o3.z

Would generate a vec2 and a vec3. We discard the second one making .z invalid!

*/
            int iNumComponents = 4;//GetMaxComponentFromComponentMask(psOperand);
			const char* StorageQualifier = "attribute";
			const char* InputName = "Input";
            const char* Precision = "";

			if(psOperand->eType == OPERAND_TYPE_INPUT_DOMAIN_POINT)
			{
				break;
			}

            if(psOperand->eType == OPERAND_TYPE_OUTPUT_CONTROL_POINT_ID)
            {
                break;
            }

            if(psOperand->eType == OPERAND_TYPE_INPUT_COVERAGE_MASK)
            {
                break;
            }

            //Already declared as part of an array.
            if(psShader->aIndexedInput[psDecl->asOperands[0].ui32RegisterNumber] == -1)
            {
                break;
            }

			if(psShader->eShaderType == GEOMETRY_SHADER)
			{
				InputName = "VtxOutput";
			}

            if(psShader->eShaderType == HULL_SHADER)
            {
                InputName = "VtxGeoOutput";
            }

            if(psShader->eShaderType == DOMAIN_SHADER)
            {
                InputName = "HullOutput";
            }

			if(InOutSupported(psContext->psShader->eTargetLanguage))
			{
				StorageQualifier = "in";
			}

            if(HavePrecisionQualifers(psShader->eTargetLanguage))
            {
                switch(psOperand->eMinPrecision)
                {
                    case OPERAND_MIN_PRECISION_DEFAULT:
                    {
                        Precision = "highp";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_FLOAT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_FLOAT_2_8:
                    {
                        Precision = "lowp";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_SINT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_UINT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                }
            }

			//Prevent multiple declarations caused by register packing.
			bformata(glsl, "#ifndef Input%d_CREATED\n", psDecl->asOperands[0].ui32RegisterNumber);
			bformata(glsl, "#define Input%d_CREATED\n", psDecl->asOperands[0].ui32RegisterNumber);

            if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage) ||
                
              (psShader->eShaderType == VERTEX_SHADER && HaveLimitedInOutLocationQualifier(psContext->psShader->eTargetLanguage)) )
            {
                bformata(glsl, "layout(location = %d) ", psDecl->asOperands[0].ui32RegisterNumber);
            }

            switch(psOperand->iIndexDims)
            {
                case INDEX_2D:
                {
                    if(iNumComponents == 1)
                    {
						const uint32_t regNum =  psDecl->asOperands[0].ui32RegisterNumber;
						const uint32_t arraySize = psDecl->asOperands[0].aui32ArraySizes[0];

						psContext->psShader->abScalarInput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                        bformata(glsl, "%s %s float %s%d [%d];\n", StorageQualifier, Precision, InputName, regNum,
                            arraySize);
                    }
                    else
                    {
                        bformata(glsl, "%s %s vec%d %s%d [%d];\n", StorageQualifier, Precision, iNumComponents, InputName, psDecl->asOperands[0].ui32RegisterNumber,
                            psDecl->asOperands[0].aui32ArraySizes[0]);
                    }
                    break;
                }
                default:
                {
                    if(iNumComponents == 1)
                    {
						psContext->psShader->abScalarInput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                        bformata(glsl, "%s %s float %s%d;\n", StorageQualifier, Precision, InputName, psDecl->asOperands[0].ui32RegisterNumber);
                    }
                    else
                    {
                        bformata(glsl, "%s %s vec%d %s%d", StorageQualifier, Precision, iNumComponents, InputName, psDecl->asOperands[0].ui32RegisterNumber);

                        if(psShader->aIndexedInput[psDecl->asOperands[0].ui32RegisterNumber])
                        {
                            bformata(glsl, "[%d]", psShader->aIndexedInput[psDecl->asOperands[0].ui32RegisterNumber]);
                        }

                        bcatcstr(glsl, ";\n");
                    }
                    break;
                }
            }

			if(psShader->eShaderType == GEOMETRY_SHADER)
			{
				bformata(glsl, "#define Input%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber,
					psDecl->asOperands[0].ui32RegisterNumber);
			}

            if(psShader->eShaderType == HULL_SHADER)
            {
				bformata(glsl, "#define Input%d VtxGeoOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber,
					psDecl->asOperands[0].ui32RegisterNumber);
            }

            if(psShader->eShaderType == DOMAIN_SHADER)
            {
				bformata(glsl, "#define Input%d HullOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber,
					psDecl->asOperands[0].ui32RegisterNumber);
            }

			bcatcstr(glsl, "#endif\n");
            break;
        }
		case OPCODE_DCL_INPUT_SIV:
		{
			break;
		}
        case OPCODE_DCL_INPUT_PS:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
            int iNumComponents = 4;//GetMaxComponentFromComponentMask(psOperand);
			const char* StorageQualifier = "varying";
            const char* Precision = "";
            const char* InputName = "VtxGeoOutput";
            const char* Interpolation = "";

			if(InOutSupported(psContext->psShader->eTargetLanguage))
			{
				StorageQualifier = "in";
			}

            switch(psDecl->value.eInterpolation)
            {
                case INTERPOLATION_CONSTANT:
                {
                    Interpolation = "flat";
                    break;
                }
                case INTERPOLATION_LINEAR:
                {
                    break;
                }
                case INTERPOLATION_LINEAR_CENTROID:
                {
                    Interpolation = "centroid";
                    break;
                }
                case INTERPOLATION_LINEAR_NOPERSPECTIVE:
                {
                    Interpolation = "noperspective";
                    break;
                }
                case INTERPOLATION_LINEAR_NOPERSPECTIVE_CENTROID:
                {
                    Interpolation = "noperspective centroid";
                    break;
                }
                case INTERPOLATION_LINEAR_SAMPLE:
                {
                    Interpolation = "sample";
                    break;
                }
                case INTERPOLATION_LINEAR_NOPERSPECTIVE_SAMPLE:
                {
                    Interpolation = "noperspective sample";
                    break;
                }
            }

            if(HavePrecisionQualifers(psShader->eTargetLanguage))
            {
                switch(psOperand->eMinPrecision)
                {
                    case OPERAND_MIN_PRECISION_DEFAULT:
                    {
                        Precision = "highp";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_FLOAT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_FLOAT_2_8:
                    {
                        Precision = "lowp";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_SINT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_UINT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                }
            }

            if(psContext->flags & HLSLCC_FLAG_TESS_ENABLED)
            {
                InputName = "DomOutput";
            }

            if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage))
            {
                bformata(glsl, "layout(location = %d) ", psDecl->asOperands[0].ui32RegisterNumber);
            }

            if(iNumComponents == 1)
            {
                bformata(glsl, "%s %s %s float %s%d;\n", Interpolation, StorageQualifier, Precision, InputName, psDecl->asOperands[0].ui32RegisterNumber);
				bformata(glsl, "vec1 Input%d = vec1(%s%d);\n", psDecl->asOperands[0].ui32RegisterNumber, InputName, psDecl->asOperands[0].ui32RegisterNumber);
            }
            else
            {
                bformata(glsl, "%s %s %s vec%d %s%d;\n", Interpolation, StorageQualifier, Precision, iNumComponents, InputName, psDecl->asOperands[0].ui32RegisterNumber);
				bformata(glsl, "#define Input%d %s%d\n", psDecl->asOperands[0].ui32RegisterNumber, InputName, psDecl->asOperands[0].ui32RegisterNumber);
            }
            
            break;
        }
        case OPCODE_DCL_TEMPS:
        {
            uint32_t i = 0; 
            const uint32_t ui32NumTemps = psDecl->value.ui32NumTemps;

            for(i=0; i < ui32NumTemps; ++i)
            {
                 bformata(glsl, "vec4 Temp%d;\n", i);
            }
            break;
        }
        case OPCODE_DCL_CONSTANT_BUFFER:
        {
			const Operand* psOperand = &psDecl->asOperands[0];
            const uint32_t ui32BindingPoint = psOperand->aui32ArraySizes[0];

            const char* StageName = "VS";
            switch(psContext->psShader->eShaderType)
            {
                case PIXEL_SHADER:
                {
                    StageName = "PS";
                    break;
                }
                case HULL_SHADER:
                {
                    StageName = "HS";
                    break;
                }
                case DOMAIN_SHADER:
                {
                    StageName = "DS";
                    break;
                }
                case GEOMETRY_SHADER:
                {
                    StageName = "GS";
                    break;
                }
                default:
                {
                    break;
                }
            }

#if CBUFFER_USE_STRUCT_AND_NAMES
            {
                ConstantBuffer* psCBuf = NULL;
                uint32_t ui32Member = 0;
                char* pszContBuffName;
                int iUseUniformBlock = 0;
                GetConstantBufferFromBindingPoint(ui32BindingPoint, &psContext->psShader->sInfo, &psCBuf);

                pszContBuffName = psCBuf->Name;

                if(psContext->flags & HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT)
                {
                    iUseUniformBlock = 1;
                }
                
                if(psCBuf->Name[0] == '$')//$Global or $Param
                {
                    pszContBuffName++;

                    if(psContext->flags & HLSLCC_FLAG_GLOBAL_CONSTS_NEVER_IN_UBO)
                    {
                        iUseUniformBlock = 0;
                    }
                }

                if(HaveUniformBindingsAndLocations(psContext->psShader->eTargetLanguage))
                {
                    if(iUseUniformBlock)
                        bformata(glsl, "layout(binding = %d) ", ui32BindingPoint);
                    else
                        bformata(glsl, "layout(location = %d) ", ui32BindingPoint);
                }

                if(iUseUniformBlock)
                    bformata(glsl, "uniform %s%s_TAG {\n", pszContBuffName, StageName);

                bformata(glsl, "uniform struct %s%s_TAG {\n", pszContBuffName, StageName);
                
                for(ui32Member=0; ui32Member < psCBuf->ui32NumVars; ++ui32Member)
                {
                    ShaderVar* psVar = &psCBuf->asVars[ui32Member];

                    bformata(glsl, "\t vec4 %s;\n", psVar->Name);
                }

                bformata(glsl, "} %s%s;\n", pszContBuffName, StageName);
            }
#else
            if(psContext->flags & HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT)
            {
                ConstantBuffer* psCBuf = NULL;
                GetConstantBufferFromBindingPoint(ui32BindingPoint, &psContext->psShader->sInfo, &psCBuf);

                /*
                    [layout(binding = X)] uniform UniformBufferName
                    {
                        vec4 ConstsX[numConsts];
                    };
                */
				if(psCBuf->Name[0] == '$')
				{
					if(psContext->flags & HLSLCC_FLAG_GLOBAL_CONSTS_NEVER_IN_UBO)
					{
                        if(HaveUniformBindingsAndLocations(psContext->psShader->eTargetLanguage))
                            bformata(glsl, "layout(location = %d) ", ui32BindingPoint);
						bcatcstr(glsl, "uniform vec4 ");
						TranslateOperand(psContext, psOperand, TO_FLAG_NONE);
						bcatcstr(glsl, ";\n");
					}
					else
					{
                        if(HaveUniformBindingsAndLocations(psContext->psShader->eTargetLanguage))
                            bformata(glsl, "layout(binding = %d) ", ui32BindingPoint);

						bformata(glsl, "uniform Globals%s {\n\tvec4 ", StageName);
                        TranslateOperand(psContext, psOperand, TO_FLAG_NONE);
						bcatcstr(glsl, ";\n};\n");
					}
				}
				else
				{
                    if(HaveUniformBindingsAndLocations(psContext->psShader->eTargetLanguage))
                        bformata(glsl, "layout(binding = %d)", ui32BindingPoint);

					bformata(glsl, "uniform %s {\n\tvec4 ", psCBuf->Name);
                        //Make it the same size accross all shader types by using the constant buffer total size rather than the largest-used-in-this-shader size.
                        bformata(glsl, "Const%d[%d]", psOperand->aui32ArraySizes[0], (int)ceil(psCBuf->ui32TotalSizeInBytes / 16.0f));//16 bytes in a vec4 float.
					bcatcstr(glsl, ";\n};\n");
				}
            }
            else
            {
                /* [layout (location = X)] uniform vec4 HLSLConstantBufferName[numConsts]; */
                if(HaveUniformBindingsAndLocations(psContext->psShader->eTargetLanguage))
                    bformata(glsl, "layout(location = %d) ", ui32BindingPoint);
                bcatcstr(glsl, "uniform vec4 ");
                TranslateOperand(psContext, psOperand, TO_FLAG_NONE);
                bcatcstr(glsl, ";\n");
            }
#endif
            break;
        }
        case OPCODE_DCL_RESOURCE:
        {
            if(HaveUniformBindingsAndLocations(psContext->psShader->eTargetLanguage))
            {
                //Constant buffer locations start at 0. Resource locations start at ui32NumConstantBuffers.
                bformata(glsl, "layout(location = %d) ", 
                    psContext->psShader->sInfo.ui32NumConstantBuffers + psDecl->asOperands[0].ui32RegisterNumber);
            }

            switch(psDecl->value.eResourceDimension)
            {
                case RESOURCE_DIMENSION_BUFFER:
                {
                    bcatcstr(glsl, "uniform samplerBuffer ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1D:
                {
					if(psDecl->ui32IsShadowTex)
                    {
                        //Create shadow and non-shadow sampler.
                        //HLSL does not have separate types for depth compare, just different functions.
						bcatcstr(glsl, "uniform sampler1DShadow ");
                        TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 1);
                        bcatcstr(glsl, ";\n");
                    }

					bcatcstr(glsl, "uniform sampler1D ");
                    TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 0);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2D:
                {
					if(psDecl->ui32IsShadowTex)
                    {
                        //Create shadow and non-shadow sampler.
                        //HLSL does not have separate types for depth compare, just different functions.
						bcatcstr(glsl, "uniform sampler2DShadow ");
                        TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 1);
                        bcatcstr(glsl, ";\n");
                    }

					bcatcstr(glsl, "uniform sampler2D ");
                    TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 0);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMS:
                {
                    bcatcstr(glsl, "uniform sampler2DMS ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE3D:
                {
                    bcatcstr(glsl, "uniform sampler3D ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBE:
                {
					if(psDecl->ui32IsShadowTex)
                    {
                        //Create shadow and non-shadow sampler.
                        //HLSL does not have separate types for depth compare, just different functions.
						bcatcstr(glsl, "uniform samplerCubeShadow ");
                        TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 1);
                        bcatcstr(glsl, ";\n");
                    }

					bcatcstr(glsl, "uniform samplerCube ");
                    TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 0);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1DARRAY:
                {
					if(psDecl->ui32IsShadowTex)
                    {
                        //Create shadow and non-shadow sampler.
                        //HLSL does not have separate types for depth compare, just different functions.
						bcatcstr(glsl, "uniform sampler1DArrayShadow ");
                        TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 1);
                        bcatcstr(glsl, ";\n");
                    }

					bcatcstr(glsl, "uniform sampler1DArray ");
                    TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 0);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DARRAY:
                {
					if(psDecl->ui32IsShadowTex)
                    {
                        //Create shadow and non-shadow sampler.
                        //HLSL does not have separate types for depth compare, just different functions.
						bcatcstr(glsl, "uniform sampler2DArrayShadow ");
                        TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 1);
                        bcatcstr(glsl, ";\n");
                    }

					bcatcstr(glsl, "uniform sampler2DArray ");
                    TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 0);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
                {
                    bcatcstr(glsl, "uniform sampler3DArray ");
                    TranslateOperand(psContext, &psDecl->asOperands[0], TO_FLAG_NONE);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
                {
					if(psDecl->ui32IsShadowTex)
                    {
                        //Create shadow and non-shadow sampler.
                        //HLSL does not have separate types for depth compare, just different functions.
						bcatcstr(glsl, "uniform samplerCubeArrayShadow ");
                        TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 1);
                        bcatcstr(glsl, ";\n");
                    }

					bcatcstr(glsl, "uniform samplerCubeArray ");
                    TextureName(psContext, psDecl->asOperands[0].ui32RegisterNumber, 0);
                    break;
                }
            }
            bcatcstr(glsl, ";\n");
            ASSERT(psDecl->asOperands[0].ui32RegisterNumber < MAX_TEXTURES);
            psShader->aeResourceDims[psDecl->asOperands[0].ui32RegisterNumber] = psDecl->value.eResourceDimension;
            break;
        }
        case OPCODE_DCL_OUTPUT:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
            const char* Precision = "";
            const char* type = "vec";

            if(HavePrecisionQualifers(psShader->eTargetLanguage))
            {
                switch(psOperand->eMinPrecision)
                {
                    case OPERAND_MIN_PRECISION_DEFAULT:
                    {
                        Precision = "highp";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_FLOAT_16:
                    {
                        Precision = "mediump";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_FLOAT_2_8:
                    {
                        Precision = "lowp";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_SINT_16:
                    {
                        Precision = "mediump";
                        //type = "ivec";
                        break;
                    }
                    case OPERAND_MIN_PRECISION_UINT_16:
                    {
                        Precision = "mediump";
                        //type = "uvec";
                        break;
                    }
                }
            }

			switch(psShader->eShaderType)
			{
				case PIXEL_SHADER:
				{
					switch(psDecl->asOperands[0].eType)
					{
                        case OPERAND_TYPE_OUTPUT_COVERAGE_MASK:
						case OPERAND_TYPE_OUTPUT_DEPTH:
						{

							break;
						}
						case OPERAND_TYPE_OUTPUT_DEPTH_GREATER_EQUAL:
						{
							bcatcstr(glsl, "#ifdef GL_ARB_conservative_depth\n");
							bcatcstr(glsl, "layout (depth_greater) out float gl_FragDepth;\n");
							bcatcstr(glsl, "#endif\n");
							break;
						}
						case OPERAND_TYPE_OUTPUT_DEPTH_LESS_EQUAL:
						{
							bcatcstr(glsl, "#ifdef GL_ARB_conservative_depth\n");
							bcatcstr(glsl, "layout (depth_less) out float gl_FragDepth;\n");
							bcatcstr(glsl, "#endif\n");
							break;
						}
						default:
						{
							if(WriteToFragData(psContext->psShader->eTargetLanguage))
							{
								bformata(glsl, "#define Output%d gl_FragData[%d]\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
							}
							else
							{
                                if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage) || HaveLimitedInOutLocationQualifier(psContext->psShader->eTargetLanguage))
                                {
                                    uint32_t index = 0;
                                    uint32_t renderTarget = psDecl->asOperands[0].ui32RegisterNumber;

                                    if((psContext->flags & HLSLCC_DUAL_SOURCE_BLENDING) && DualSourceBlendSupported(psContext->psShader->eTargetLanguage))
                                    {
                                        if(renderTarget > 0)
                                        {
                                            renderTarget = 0;
                                            index = 1;
                                        }
                                        bformata(glsl, "layout(location = %d, index = %d) ", renderTarget, index);
                                    }
                                    else
                                    {
                                        bformata(glsl, "layout(location = %d) ", renderTarget);
                                    }
                                }

								bformata(glsl, "out %s %s4 PixOutput%d;\n", Precision, type, psDecl->asOperands[0].ui32RegisterNumber);
								bformata(glsl, "#define Output%d PixOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
							}
							break;
						}
					}
					break;
				}
				case VERTEX_SHADER:
				{
					int iNumComponents = 4;//GetMaxComponentFromComponentMask(&psDecl->asOperands[0]);

                    if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage))
                    {
                        bformata(glsl, "layout(location = %d) ", psDecl->asOperands[0].ui32RegisterNumber);
                    }

					if(psContext->flags & HLSLCC_FLAG_GS_ENABLED)
					{
						bformata(glsl, "out vec%d VtxOutput%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
						bformata(glsl, "#define Output%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					}
					else
					{
						if(InOutSupported(psContext->psShader->eTargetLanguage))
						{
							bformata(glsl, "out %s vec%d VtxGeoOutput%d;\n", Precision, iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
						}
						else
						{
							bformata(glsl, "varying %s %s%d VtxGeoOutput%d;\n", Precision, type, iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
						}
						bformata(glsl, "#define Output%d VtxGeoOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					}
					break;
				}
				case GEOMETRY_SHADER:
				{
					/*
						The *_CREATED preprocessor code here is designed to ensure that if fxc 
						packs multiple outputs into a vector and generates something like
						dcl_output o3.xy
						dcl_output o3.z
						then the vector (output3 in the above case) will only be declared once.
					*/
					bformata(glsl, "#ifndef VtxGeoOutput%d_CREATED\n", psDecl->asOperands[0].ui32RegisterNumber);
					bformata(glsl, "#define VtxGeoOutput%d_CREATED\n", psDecl->asOperands[0].ui32RegisterNumber);

                    if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage))
                    {
                        bformata(glsl, "layout(location = %d) ", psDecl->asOperands[0].ui32RegisterNumber);
                    }

					bformata(glsl, "out vec4 VtxGeoOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
					bformata(glsl, "#define Output%d VtxGeoOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					bcatcstr(glsl, "#endif\n");
					break;
				}
				case HULL_SHADER:
				{
                    if(psDecl->asOperands[0].ui32RegisterNumber==0)
                    {
                       bcatcstr(glsl, "#define Output0 gl_out[gl_InvocationID].gl_Position\n");
                    }
                    else
                    {
                        if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage))
                        {
                            bformata(glsl, "layout(location = %d) ", psDecl->asOperands[0].ui32RegisterNumber);
                        }
					    bformata(glsl, "out vec4 HullOutput%d[];\n", psDecl->asOperands[0].ui32RegisterNumber);
					    bformata(glsl, "#define Output%d HullOutput%d[gl_InvocationID]\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
                    }
					break;
				}
				case DOMAIN_SHADER:
				{
                    if(HaveInOutLocationQualifier(psContext->psShader->eTargetLanguage))
                    {
                        bformata(glsl, "layout(location = %d) ", psDecl->asOperands[0].ui32RegisterNumber);
                    }
					bformata(glsl, "out vec4 DomOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
					bformata(glsl, "#define Output%d DomOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					break;
				}
			}
            break;
        }
        case OPCODE_DCL_GLOBAL_FLAGS:
        {
            uint32_t ui32Flags = psDecl->value.ui32GlobalFlags;
            
            if(ui32Flags & GLOBAL_FLAG_FORCE_EARLY_DEPTH_STENCIL)
            {
                bcatcstr(glsl, "layout(early_fragment_tests) in;\n");
            }
            if(!(ui32Flags & GLOBAL_FLAG_REFACTORING_ALLOWED))
            {
                //TODO add precise
                //HLSL precise - http://msdn.microsoft.com/en-us/library/windows/desktop/hh447204(v=vs.85).aspx
            }
            if(ui32Flags & GLOBAL_FLAG_ENABLE_DOUBLE_PRECISION_FLOAT_OPS)
            {
                bcatcstr(glsl, "#extension GL_ARB_gpu_shader_fp64 : enable\n");
            }
            break;
        }

        case OPCODE_DCL_THREAD_GROUP:
        {
            bformata(glsl, "layout(local_size_x = %d, local_size_y = %d, local_size_z = %d) in;\n",
                psDecl->value.aui32WorkGroupSize[0],
                psDecl->value.aui32WorkGroupSize[1],
                psDecl->value.aui32WorkGroupSize[2]);
            break;
        }
        case OPCODE_DCL_TESS_OUTPUT_PRIMITIVE:
        {
            if(psContext->psShader->eShaderType == HULL_SHADER)
            {
                psContext->psShader->sInfo.eTessOutPrim = psDecl->value.eTessOutPrim;
            }
            break;
        }
        case OPCODE_DCL_TESS_DOMAIN:
        {
			if(psContext->psShader->eShaderType == DOMAIN_SHADER)
			{
				switch(psDecl->value.eTessDomain)
				{
					case TESSELLATOR_DOMAIN_ISOLINE:
					{
						bcatcstr(glsl, "layout(isolines) in;\n");
						break;
					}
					case TESSELLATOR_DOMAIN_TRI:
					{
						bcatcstr(glsl, "layout(triangles) in;\n");
						break;
					}
					case TESSELLATOR_DOMAIN_QUAD:
					{
						bcatcstr(glsl, "layout(quads) in;\n");
						break;
					}
					default:
					{
						break;
					}
				}
			}
            break;
        }
        case OPCODE_DCL_TESS_PARTITIONING:
        {
            if(psContext->psShader->eShaderType == HULL_SHADER)
            {
                psContext->psShader->sInfo.eTessPartitioning = psDecl->value.eTessPartitioning;
            }
            break;
        }
        case OPCODE_DCL_GS_OUTPUT_PRIMITIVE_TOPOLOGY:
        {
            switch(psDecl->value.eOutputPrimitiveTopology)
            {
                case PRIMITIVE_TOPOLOGY_POINTLIST:
                {
                    bcatcstr(glsl, "layout(points) out;\n");
                    break;
                }
                case PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
                case PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
                case PRIMITIVE_TOPOLOGY_LINELIST:
                case PRIMITIVE_TOPOLOGY_LINESTRIP:
                {
                    bcatcstr(glsl, "layout(line_strip) out;\n");
                    break;
                }

                case PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
                case PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
                case PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
                case PRIMITIVE_TOPOLOGY_TRIANGLELIST:
                {
                    bcatcstr(glsl, "layout(triangle_strip) out;\n");
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case OPCODE_DCL_MAX_OUTPUT_VERTEX_COUNT:
        {
            bformata(glsl, "layout(max_vertices = %d) out;\n", psDecl->value.ui32MaxOutputVertexCount);
            break;
        }
        case OPCODE_DCL_GS_INPUT_PRIMITIVE:
        {
            switch(psDecl->value.eInputPrimitive)
            {
                case PRIMITIVE_POINT:
                {
                    bcatcstr(glsl, "layout(points) in;\n");
                    break;
                }
                case PRIMITIVE_LINE:
                {
                    bcatcstr(glsl, "layout(lines) in;\n");
                    break;
                }
                case PRIMITIVE_LINE_ADJ:
                {
                    bcatcstr(glsl, "layout(lines_adjacency) in;\n");
                    break;
                }
                case PRIMITIVE_TRIANGLE:
                {
                    bcatcstr(glsl, "layout(triangles) in;\n");
                    break;
                }
                case PRIMITIVE_TRIANGLE_ADJ:
                {
                    bcatcstr(glsl, "layout(triangles_adjacency) in;\n");
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case OPCODE_DCL_INTERFACE:
        {
            uint32_t func = 0;
            const uint32_t interfaceID = psDecl->value.interface.ui32InterfaceID;
            const uint32_t numUniforms = psDecl->value.interface.ui32ArraySize;
            const uint32_t ui32NumBodiesPerTable = psContext->psShader->funcPointer[interfaceID].ui32NumBodiesPerTable;
            ShaderVar* psVar;
            uint32_t varFound;

            const char* uniformName;
            
            varFound = GetInterfaceVarFromOffset(interfaceID, &psContext->psShader->sInfo, &psVar);
            ASSERT(varFound);
            uniformName = &psVar->Name[0];

            bformata(glsl, "subroutine uniform SubroutineType %s[%d*%d];\n", uniformName, numUniforms, ui32NumBodiesPerTable);
            break;
        }
        case OPCODE_DCL_FUNCTION_BODY:
        {
            //bformata(glsl, "void Func%d();//%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].eType);
            break;
        }
        case OPCODE_DCL_FUNCTION_TABLE:
        {
            break;
        }
		case OPCODE_CUSTOMDATA:
		{
			const uint32_t ui32NumVec4 = psDecl->ui32NumOperands;
			const uint32_t ui32NumVec4Minus1 = (ui32NumVec4-1);
			uint32_t ui32ConstIndex = 0;
			float x, y, z, w;

			//If ShaderBitEncodingSupported then 1 integer buffer, use intBitsToFloat to get float values. - More instructions.
			//else 2 buffers - one integer and one float. - More data

			if(ShaderBitEncodingSupported(psShader->eTargetLanguage) == 0)
			{
				bcatcstr(glsl, "#define immediateConstBufferI(idx) immediateConstBufferInt[idx]\n");
				bcatcstr(glsl, "#define immediateConstBufferF(idx) immediateConstBuffer[idx]\n");

				bformata(glsl, "vec4 immediateConstBuffer[%d] = vec4[%d] (\n", ui32NumVec4, ui32NumVec4);
				for(;ui32ConstIndex < ui32NumVec4Minus1; ui32ConstIndex++)
				{
					float loopLocalX, loopLocalY, loopLocalZ, loopLocalW;
					loopLocalX = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].a;
					loopLocalY = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].b;
					loopLocalZ = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].c;
					loopLocalW = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].d;

					//A single vec4 can mix integer and float types.
					//Forced NAN and INF to zero inside the immediate constant buffer. This will allow the shader to compile.
					if(fpcheck(loopLocalX))
					{
						loopLocalX = 0;
					}
					if(fpcheck(loopLocalY))
					{
						loopLocalY = 0;
					}
					if(fpcheck(loopLocalZ))
					{
						loopLocalZ = 0;
					}
					if(fpcheck(loopLocalW))
					{
						loopLocalW = 0;
					}

					bformata(glsl, "\tvec4(%f, %f, %f, %f), \n", loopLocalX, loopLocalY, loopLocalZ, loopLocalW);
				}
				//No trailing comma on this one
				x = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].a;
				y = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].b;
				z = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].c;
				w = *(float*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].d;
				if(fpcheck(x))
				{
					x = 0;
				}
				if(fpcheck(y))
				{
					y = 0;
				}
				if(fpcheck(z))
				{
					z = 0;
				}
				if(fpcheck(w))
				{
					w = 0;
				}
				bformata(glsl, "\tvec4(%f, %f, %f, %f)\n", x, y, z, w);
				bcatcstr(glsl, ");\n");
			}
			else
			{
				bcatcstr(glsl, "#define immediateConstBufferI(idx) immediateConstBufferInt[idx]\n");
				bcatcstr(glsl, "#define immediateConstBufferF(idx) intBitsToFloat(immediateConstBufferInt[idx])\n");
			}

			{
			uint32_t ui32ConstIndex = 0;
			int x, y, z, w;

			bformata(glsl, "ivec4 immediateConstBufferInt[%d] = ivec4[%d] (\n", ui32NumVec4, ui32NumVec4);
			for(;ui32ConstIndex < ui32NumVec4Minus1; ui32ConstIndex++)
			{
				int loopLocalX, loopLocalY, loopLocalZ, loopLocalW;
				loopLocalX = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].a;
				loopLocalY = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].b;
				loopLocalZ = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].c;
				loopLocalW = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].d;

				bformata(glsl, "\tivec4(%d, %d, %d, %d), \n", loopLocalX, loopLocalY, loopLocalZ, loopLocalW);
			}
			//No trailing comma on this one
			x = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].a;
			y = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].b;
			z = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].c;
			w = *(int*)&psDecl->asImmediateConstBuffer[ui32ConstIndex].d;

			bformata(glsl, "\tivec4(%d, %d, %d, %d)\n", x, y, z, w);
			bcatcstr(glsl, ");\n");
			}

			break;
		}
        case OPCODE_DCL_HS_FORK_PHASE_INSTANCE_COUNT:
        {
            const uint32_t forkPhaseNum = psDecl->value.aui32HullPhaseInstanceInfo[0];
            const uint32_t instanceCount = psDecl->value.aui32HullPhaseInstanceInfo[1];
            bformata(glsl, "const int HullPhase%dInstanceCount = %d;\n", forkPhaseNum, instanceCount);
            break;
        }
        case OPCODE_DCL_INDEX_RANGE:
        {
            break;
        }
        case OPCODE_HS_DECLS:
        {
            break;
        }
        case OPCODE_DCL_INPUT_CONTROL_POINT_COUNT:
        {
            break;
        }
        case OPCODE_DCL_OUTPUT_CONTROL_POINT_COUNT:
        {
            if(psContext->psShader->eShaderType == HULL_SHADER)
            {
                bformata(glsl, "layout(vertices=%d) out;\n", psDecl->value.ui32MaxOutputVertexCount);
            }
            break;
        }
        case OPCODE_HS_FORK_PHASE:
        {
            break;
        }
        case OPCODE_HS_JOIN_PHASE:
        {
            break;
        }
		case OPCODE_DCL_SAMPLER:
		{
			break;
		}
        case OPCODE_DCL_HS_MAX_TESSFACTOR:
        {
            //For GLSL the max tessellation factor is fixed to the value of gl_MaxTessGenLevel. 
            break;
        }
        default:
        {
            ASSERT(0);
            break;
        }
    }
}

//Convert from per-phase temps to global temps for GLSL.
void ConsolidateHullTempVars(Shader* psShader)
{
    uint32_t i, k;
    const uint32_t ui32NumDeclLists = 3+psShader->ui32ForkPhaseCount;
    Declaration* pasDeclArray[3+MAX_FORK_PHASES];
    uint32_t aui32DeclCounts[3+MAX_FORK_PHASES];
    uint32_t ui32NumTemps = 0;

    i = 0;

    pasDeclArray[i] = psShader->psHSDecl;
    aui32DeclCounts[i++] = psShader->ui32HSDeclCount;

    pasDeclArray[i] = psShader->psHSControlPointPhaseDecl;
    aui32DeclCounts[i++] = psShader->ui32HSControlPointDeclCount;
    for(k=0; k < psShader->ui32ForkPhaseCount; ++k)
    {
        pasDeclArray[i] = psShader->apsHSForkPhaseDecl[k];
        aui32DeclCounts[i++] = psShader->aui32HSForkDeclCount[k];
    }
    pasDeclArray[i] = psShader->psHSJoinPhaseDecl;
    aui32DeclCounts[i++] = psShader->ui32HSJoinDeclCount;

    for(k = 0; k < ui32NumDeclLists; ++k)
    {
        for(i=0; i < aui32DeclCounts[k]; ++i)
        {
            Declaration* psDecl = pasDeclArray[k]+i;
 
            if(psDecl->eOpcode == OPCODE_DCL_TEMPS)
            {
                if(ui32NumTemps < psDecl->value.ui32NumTemps)
                {
                    //Find the total max number of temps needed by the entire
                    //shader.
                    ui32NumTemps = psDecl->value.ui32NumTemps;
                }
                //Only want one global temp declaration.
                psDecl->value.ui32NumTemps = 0;
            }
        }
    }

    //Find the first temp declaration and make it
    //declare the max needed amount of temps.
    for(k = 0; k < ui32NumDeclLists; ++k)
    {
        for(i=0; i < aui32DeclCounts[k]; ++i)
        {
            Declaration* psDecl = pasDeclArray[k]+i;
 
            if(psDecl->eOpcode == OPCODE_DCL_TEMPS)
            {
                psDecl->value.ui32NumTemps = ui32NumTemps;
                return;
            }
        }
    }
}

