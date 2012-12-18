#include "toGLSL.h"
#include "toGLSLDeclaration.h"
#include "toGLSLOperand.h"
#include "bstrlib.h"
#include "assert.h"
#include <math.h>

#include <float.h>

#ifdef _MSC_VER
#define isnan(x) _isnan(x)
#define isinf(x) (!_finite(x))
#endif

#define fpcheck(x) (isnan(x) || isinf(x))

#ifdef _DEBUG
#define ASSERT(expr) assert(expr)
#else
#define ASSERT(expr)
#endif

extern void AddIndentation(HLSLCrossCompilerContext* psContext);

void TranslateDeclaration(HLSLCrossCompilerContext* psContext, const Declaration* psDecl)
{
    bstring glsl = psContext->glsl;
    Shader* psShader = psContext->psShader;

    switch(psDecl->eOpcode)
    {
        case OPCODE_DCL_INPUT_PS_SGV:
        {
            switch(psDecl->asOperands[0].eSpecialName)
            {
                case NAME_POSITION:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_Position\n");
                    break;
                }
                /*
                    HLSL allows .x on scalars. Upgrade scalar
                    system values to vec1 so .x works. Even when
                    GLSL allows a vec1, this will still be needed for
                    backwards compatiblility.
                */
                case NAME_RENDER_TARGET_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_Layer)\n");
                    break;
                }
                case NAME_CLIP_DISTANCE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_ClipDistance\n");
                    break;
                }
                case NAME_VIEWPORT_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_ViewportIndex)\n");
                    break;
                }
                case NAME_VERTEX_ID:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_VertexID)\n");
                    break;
                }
                case NAME_PRIMITIVE_ID:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateSystemValueVariableName(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_PrimitiveID);\n");
                    break;
                }
                case NAME_INSTANCE_ID:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateSystemValueVariableName(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_InstanceID)\n");
                    break;
                }
                case NAME_IS_FRONT_FACE:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateSystemValueVariableName(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_FrontFacing)\n");
                    break;
                }
                default:
                {
                    bformata(glsl, "in vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
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
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_Position\n");
                    break;
                }
                case NAME_RENDER_TARGET_ARRAY_INDEX:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;
					psContext->psShader->abIntegerOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;
                    bcatcstr(glsl, "#define ");
					TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_Layer\n");
                    break;
                }
                case NAME_CLIP_DISTANCE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_ClipDistance\n");
                    break;
                }
                case NAME_VIEWPORT_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_ViewportIndex\n");
                    break;
                }
                case NAME_VERTEX_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_VertexID\n");
                    break;
                }
                case NAME_PRIMITIVE_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_PrimitiveID);\n");
                    break;
                }
                case NAME_INSTANCE_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_InstanceID\n");
                    break;
                }
                case NAME_IS_FRONT_FACE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_FrontFacing\n");
                    break;
                }
		        case NAME_FINAL_QUAD_U_EQ_0_EDGE_TESSFACTOR:
		        case NAME_FINAL_QUAD_V_EQ_0_EDGE_TESSFACTOR: 
		        case NAME_FINAL_QUAD_U_EQ_1_EDGE_TESSFACTOR: 
		        case NAME_FINAL_QUAD_V_EQ_1_EDGE_TESSFACTOR:
		        case NAME_FINAL_TRI_U_EQ_0_EDGE_TESSFACTOR:
		        case NAME_FINAL_TRI_V_EQ_0_EDGE_TESSFACTOR:
		        case NAME_FINAL_TRI_W_EQ_0_EDGE_TESSFACTOR:
		        case NAME_FINAL_LINE_DETAIL_TESSFACTOR:
		        case NAME_FINAL_LINE_DENSITY_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;
                    bcatcstr(glsl, "#define ");
                    TranslateSystemValueVariableName(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_TessLevelOuter\n");
                    break;
                }
		        case NAME_FINAL_QUAD_U_INSIDE_TESSFACTOR:
		        case NAME_FINAL_QUAD_V_INSIDE_TESSFACTOR:
                case NAME_FINAL_TRI_INSIDE_TESSFACTOR:
                {
					psContext->psShader->abScalarOutput[psDecl->asOperands[0].ui32RegisterNumber] = 1;
                    bcatcstr(glsl, "#define ");
                    TranslateSystemValueVariableName(psContext, &psDecl->asOperands[0]);
                    bformata(glsl, " gl_TessLevelInner\n");
                    break;
                }
                default:
                {
                    bformata(glsl, "out vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                    bcatcstr(glsl, "#define ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
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

			if(psOperand->eType == OPERAND_TYPE_INPUT_DOMAIN_POINT)
			{
				break;
			}

			if(psShader->eShaderType == GEOMETRY_SHADER)
			{
				InputName = "VtxOutput";
			}

			if(InOutSupported(psContext->psShader->eTargetLanguage))
			{
				StorageQualifier = "in";
			}

			//Prevent multiple declarations caused by register packing.
			bformata(glsl, "#ifndef Input%d_CREATED\n", psDecl->asOperands[0].ui32RegisterNumber);
			bformata(glsl, "#define Input%d_CREATED\n", psDecl->asOperands[0].ui32RegisterNumber);

            switch(psOperand->iIndexDims)
            {
                case INDEX_2D:
                {
                    if(iNumComponents == 1)
                    {
						const uint32_t regNum =  psDecl->asOperands[0].ui32RegisterNumber;
						const uint32_t arraySize = psDecl->asOperands[0].aui32ArraySizes[0];

						psContext->psShader->abScalarInput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                        bformata(glsl, "%s float %s%d [%d];\n", StorageQualifier, InputName, regNum,
                            arraySize);
                    }
                    else
                    {
                        bformata(glsl, "%s vec%d %s%d [%d];\n", StorageQualifier, iNumComponents, InputName, psDecl->asOperands[0].ui32RegisterNumber,
                            psDecl->asOperands[0].aui32ArraySizes[0]);
                    }
                    break;
                }
                default:
                {
                    if(iNumComponents == 1)
                    {
						psContext->psShader->abScalarInput[psDecl->asOperands[0].ui32RegisterNumber] = 1;

                        bformata(glsl, "%s float %s%d;\n", StorageQualifier, InputName, psDecl->asOperands[0].ui32RegisterNumber);
                    }
                    else
                    {
                        bformata(glsl, "%s vec%d %s%d;\n", StorageQualifier, iNumComponents, InputName, psDecl->asOperands[0].ui32RegisterNumber);
                    }
                    break;
                }
            }

			if(psShader->eShaderType == GEOMETRY_SHADER)
			{
				bformata(glsl, "#define Input%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber,
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

			if(InOutSupported(psContext->psShader->eTargetLanguage))
			{
				StorageQualifier = "in";
			}

            if(iNumComponents == 1)
            {
                bformata(glsl, "%s float VtxGeoOutput%d;\n", StorageQualifier, psDecl->asOperands[0].ui32RegisterNumber);
				bformata(glsl, "vec1 Input%d = vec1(VtxGeoOutput%d);\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
            }
            else
            {
                bformata(glsl, "%s vec%d VtxGeoOutput%d;\n", StorageQualifier, iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
				bformata(glsl, "#define Input%d VtxGeoOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
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
				case COMPUTE_SHADER:
				{
					StageName = "CS";
					break;
				}
                default:
                {
                    break;
                }
            }
            if(psContext->flags & HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT)
            {
				ResourceBinding* psBinding = 0;
				GetResourceFromBindingPoint(RTYPE_CBUFFER, psOperand->aui32ArraySizes[0], &psContext->psShader->sInfo, &psBinding);
                /*
                    layout(std140) uniform UniformBufferName
                    {
                        vec4 ConstsX[numConsts];
                    };
                */
				if(psBinding->Name[0] == '$')
				{
					if(psContext->flags & HLSLCC_FLAG_GLOBAL_CONSTS_NEVER_IN_UBO)
					{
						bcatcstr(glsl, "uniform vec4 ");
						TranslateOperand(psContext, psOperand);
						bcatcstr(glsl, ";\n");
					}
					else
					{
						bformata(glsl, "layout(std140) uniform Globals%s {\n\tvec4 ", StageName);
						TranslateOperand(psContext, psOperand);
						bcatcstr(glsl, ";\n};\n");
					}
				}
				else
				{
					bformata(glsl, "layout(std140) uniform %s%s {\n\tvec4 ", psBinding->Name, StageName);
					TranslateOperand(psContext, psOperand);
					bcatcstr(glsl, ";\n};\n");
				}
            }
            else
            {
                /* uniform vec4 HLSLConstantBufferName[numConsts]; */
                bcatcstr(glsl, "uniform vec4 ");
                TranslateOperand(psContext, psOperand);
                bcatcstr(glsl, ";\n");
            }
            break;
        }
        case OPCODE_DCL_RESOURCE:
        {
            switch(psDecl->value.eResourceDimension)
            {
                case RESOURCE_DIMENSION_BUFFER:
                {
                    bcatcstr(glsl, "uniform samplerBuffer ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1D:
                {
					if(psDecl->ui32IsShadowTex)
						bcatcstr(glsl, "uniform sampler1DShadow ");
					else
						bcatcstr(glsl, "uniform sampler1D ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2D:
                {
					if(psDecl->ui32IsShadowTex)
						bcatcstr(glsl, "uniform sampler2DShadow ");
					else
						bcatcstr(glsl, "uniform sampler2D ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMS:
                {
                    bcatcstr(glsl, "uniform sampler2DMS ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE3D:
                {
                    bcatcstr(glsl, "uniform sampler3D ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBE:
                {
					if(psDecl->ui32IsShadowTex)
						bcatcstr(glsl, "uniform samplerCubeShadow ");
					else
						bcatcstr(glsl, "uniform samplerCube ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1DARRAY:
                {
					if(psDecl->ui32IsShadowTex)
						bcatcstr(glsl, "uniform sampler1DArrayShadow ");
					else
						bcatcstr(glsl, "uniform sampler1DArray ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DARRAY:
                {
					if(psDecl->ui32IsShadowTex)
						bcatcstr(glsl, "uniform sampler2DArrayShadow");
					else
						bcatcstr(glsl, "uniform sampler2DArray ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
                {
                    bcatcstr(glsl, "uniform sampler3DArray ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
                {
					if(psDecl->ui32IsShadowTex)
						bcatcstr(glsl, "uniform samplerCubeArrayShadow ");
					else
						bcatcstr(glsl, "uniform samplerCubeArray ");
                    TranslateOperand(psContext, &psDecl->asOperands[0]);
                    break;
                }
            }
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_DCL_OUTPUT:
        {
			switch(psShader->eShaderType)
			{
				case PIXEL_SHADER:
				{
					switch(psDecl->asOperands[0].eType)
					{
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
								bformata(glsl, "out vec4 PixOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
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

					if(psContext->flags & HLSLCC_FLAG_GS_ENABLED)
					{
						bformata(glsl, "out vec%d VtxOutput%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
						bformata(glsl, "#define Output%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					}
					else
					{
						if(InOutSupported(psContext->psShader->eTargetLanguage))
						{
							bformata(glsl, "out vec%d VtxGeoOutput%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
						}
						else
						{
							bformata(glsl, "varying vec%d VtxGeoOutput%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
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
					bformata(glsl, "out vec4 VtxGeoOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
					bformata(glsl, "#define Output%d VtxGeoOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					bcatcstr(glsl, "#endif\n");
					break;
				}
				case HULL_SHADER:
				{
					bformata(glsl, "out vec4 HullOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
					bformata(glsl, "#define Output%d HullOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
					break;
				}
				case DOMAIN_SHADER:
				{
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
            switch(psDecl->value.eTessOutPrim)
            {
                case TESSELLATOR_OUTPUT_TRIANGLE_CW:
                {
                    bcatcstr(glsl, "layout(cw) in;\n");
                    break;
                }
                case TESSELLATOR_OUTPUT_TRIANGLE_CCW:
                {
                    bcatcstr(glsl, "layout(ccw) in;\n");
                    break;
                }
                case TESSELLATOR_OUTPUT_POINT:
                {
                    bcatcstr(glsl, "layout(point_mode) in;\n");
                    break;
                }
                case TESSELLATOR_OUTPUT_LINE:
                {
                    bcatcstr(glsl, "//TESSELLATOR_OUTPUT_LINE\n");
                    break;
                }
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
            switch(psDecl->value.eTessPartitioning)
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
                case TESSELLATOR_PARTITIONING_INTEGER:
                {
                    bcatcstr(glsl, "//TESSELLATOR_PARTITIONING_INTEGER not supported\n");
                    break;
                }
                case TESSELLATOR_PARTITIONING_POW2:
                {
                    bcatcstr(glsl, "//TESSELLATOR_PARTITIONING_POW2 not supported\n");
                    break;
                }
                default:
                {
                    break;
                }
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
            const uint32_t funcCount = psDecl->value.interface.ui32NumFunctions;
            //for(;func < funcCount; ++func)

            bformata(glsl, "subroutine void Interface%d();\n", interfaceID);

            bformata(glsl, "subroutine uniform Interface%d InterfaceVar%d;\n", interfaceID, interfaceID);
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
            const uint32_t instanceCount = psDecl->value.ui32HullPhaseInstanceCount;
            bformata(glsl, "int HullPhaseInstanceCount = %d;\n", instanceCount);
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
        default:
        {
            ASSERT(0);
            break;
        }
    }
}

