#include "toGLSLDeclaration.h"
#include "toGLSLOperand.h"
#include "bstrlib.h"

extern bstring glsl;
extern int indent;
extern void AddIndentation();

void TranslateDeclaration(Shader* psShader, const Declaration* psDecl)
{
    switch(psDecl->eOpcode)
    {
        case OPCODE_DCL_INPUT_PS_SGV:
        {
            switch(psDecl->asOperands[0].eSpecialName)
            {
                case NAME_POSITION:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
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
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_Layer)\n");
                    break;
                }
                case NAME_CLIP_DISTANCE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_ClipDistance\n");
                    break;
                }
                case NAME_VIEWPORT_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_ViewportIndex)\n");
                    break;
                }
                case NAME_VERTEX_ID:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_VertexID)\n");
                    break;
                }
                case NAME_PRIMITIVE_ID:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateSystemValueVariableName(&psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_PrimitiveID);\n");
                    break;
                }
                case NAME_INSTANCE_ID:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateSystemValueVariableName(&psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_InstanceID)\n");
                    break;
                }
                case NAME_IS_FRONT_FACE:
                {
                    bcatcstr(glsl, "vec1 ");
                    TranslateSystemValueVariableName(&psDecl->asOperands[0]);
                    bformata(glsl, " = vec1(gl_FrontFacing)\n");
                    break;
                }
                default:
                {
                    bformata(glsl, "in vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
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
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_Position\n");
                    break;
                }
                case NAME_RENDER_TARGET_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_Layer\n");
                    break;
                }
                case NAME_CLIP_DISTANCE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_ClipDistance\n");
                    break;
                }
                case NAME_VIEWPORT_ARRAY_INDEX:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_ViewportIndex\n");
                    break;
                }
                case NAME_VERTEX_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_VertexID\n");
                    break;
                }
                case NAME_PRIMITIVE_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_PrimitiveID);\n");
                    break;
                }
                case NAME_INSTANCE_ID:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_InstanceID\n");
                    break;
                }
                case NAME_IS_FRONT_FACE:
                {
                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " gl_FrontFacing\n");
                    break;
                }
                default:
                {
                    bformata(glsl, "out vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                    bcatcstr(glsl, "#define ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    bformata(glsl, " %s\n", psDecl->asOperands[0].pszSpecialName);
                    break;
                }
            }
            break;
        }
        case OPCODE_DCL_INPUT:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
            int iNumComponents = GetMaxComponentFromComponentMask(psOperand);
            switch(psOperand->iIndexDims)
            {
                case INDEX_2D:
                {
                    if(iNumComponents == 1)
                    {
                        bformata(glsl, "in float Input%d [%d];\n", psDecl->asOperands[0].ui32RegisterNumber,
                            psDecl->asOperands[0].aui32ArraySizes[0]);
                    }
                    else
                    {
                        bformata(glsl, "in vec%d Input%d [%d];\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber,
                            psDecl->asOperands[0].aui32ArraySizes[0]);
                    }
                    break;
                }
                default:
                {
                    if(iNumComponents == 1)
                    {
                        bformata(glsl, "in float Input%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
                    }
                    else
                    {
                        bformata(glsl, "in vec%d Input%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
                    }
                    break;
                }
            }
            break;
        }
        case OPCODE_DCL_INPUT_PS:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
            int iNumComponents = GetMaxComponentFromComponentMask(psOperand);
            if(iNumComponents == 1)
            {
                bformata(glsl, "in float VtxOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
            }
            else
            {
                bformata(glsl, "in vec%d VtxOutput%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
            }
            bformata(glsl, "#define Input%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
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
            bcatcstr(glsl, "uniform vec4 ");
            TranslateOperand(&psDecl->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_DCL_RESOURCE:
        {
            switch(psDecl->value.eResourceDimension)
            {
                case RESOURCE_DIMENSION_BUFFER:
                {
                    bcatcstr(glsl, "uniform samplerBuffer ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1D:
                {
                    bcatcstr(glsl, "uniform sampler1D ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2D:
                {
                    bcatcstr(glsl, "uniform sampler2D ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMS:
                {
                    bcatcstr(glsl, "uniform sampler2DMS ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE3D:
                {
                    bcatcstr(glsl, "uniform sampler3D ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBE:
                {
                    bcatcstr(glsl, "uniform samplerCube ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1DARRAY:
                {
                    bcatcstr(glsl, "uniform sampler1DArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DARRAY:
                {
                    bcatcstr(glsl, "uniform sampler2DArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
                {
                    bcatcstr(glsl, "uniform sampler3DArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
                {
                    bcatcstr(glsl, "uniform samplerCubeArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
            }
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_DCL_OUTPUT:
        {
            if(psShader->eShaderType == PIXEL_SHADER)
            {
                bformata(glsl, "out vec4 PixOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
                bformata(glsl, "#define Output%d PixOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
            }
            else
            {
                bformata(glsl, "out vec4 VtxOutput%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
                bformata(glsl, "#define Output%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
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
        default:
        {
            bformata(glsl, "/* Unhandled input declaration - opcode=0x%X */\n", psDecl->eOpcode);
            break;
        }
    }
}

