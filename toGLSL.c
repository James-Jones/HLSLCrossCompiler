#include "tokens.h"
#include "structs.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"
#include "hlsl_opcode_funcs_glsl.h"
#include "toGLSL.h"

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

bstring glsl;
int indent;

void TranslateOperand(const Operand* psOperand);

int GetMaxComponentFromComponentMask(const Operand* psOperand)
{
    if(psOperand->iWriteMaskEnabled &&
       psOperand->iNumComponents == 4)
    {
        //Comonent Mask
        if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
        {
            if(psOperand->ui32CompMask != 0 && psOperand->ui32CompMask != (OPERAND_4_COMPONENT_MASK_X|OPERAND_4_COMPONENT_MASK_Y|OPERAND_4_COMPONENT_MASK_Z|OPERAND_4_COMPONENT_MASK_W))
            {
                if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_W)
                {
                    return 4;
                }
                if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Z)
                {
                    return 3;
                }
                if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Y)
                {
                    return 2;
                }
                if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_X)
                {
                    return 1;
                }
            }
        }
    }
    return 4;
}

void AddIndentation()
{
    int i;
    for(i=0; i < indent; ++i)
    {
        bcatcstr(glsl, "    ");
    }
}

void AddVersionDependentCode(Shader* psShader)
{
    /*
        OpenGL 4.1 API spec:
        To use any built-in input or output in the gl_PerVertex block in separable
        program objects, shader code must redeclare that block prior to use.
    */
    if(psShader->eShaderType == VERTEX_SHADER)
    {
        bcatcstr(glsl, "#if __VERSION__ > 410\n");
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

void AddOpcodeFuncs()
{
    bcatcstr(glsl, "\n");

    bcatcstr(glsl, psz_hlsl_opcode_funcs_glsl);

    bcatcstr(glsl, "\n");
}

void CallHLSLOpcodeFunc1(const char* name, Instruction* psInst)
{
    AddIndentation();
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(&psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[1]);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc2(const char* name, Instruction* psInst)
{
    AddIndentation();
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(&psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[2]);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc3(const char* name, Instruction* psInst)
{
    AddIndentation();
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(&psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[2]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[3]);
    bcatcstr(glsl, ");\n");
}

void TranslateOperandSwizzle(const Operand* psOperand)
{
    if(psOperand->iWriteMaskEnabled &&
       psOperand->iNumComponents == 4)
    {
    //Comonent Mask
    if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
    {
        if(psOperand->ui32CompMask != 0 && psOperand->ui32CompMask != (OPERAND_4_COMPONENT_MASK_X|OPERAND_4_COMPONENT_MASK_Y|OPERAND_4_COMPONENT_MASK_Z|OPERAND_4_COMPONENT_MASK_W))
        {
            bcatcstr(glsl, ".");
            if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_X)
            {
                bcatcstr(glsl, "x");
            }
            if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Y)
            {
                bcatcstr(glsl, "y");
            }
            if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Z)
            {
                bcatcstr(glsl, "z");
            }
            if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_W)
            {
                bcatcstr(glsl, "w");
            }
        }
    }
    else
    //Component Swizzle
    if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
    {
        if(psOperand->ui32Swizzle != (NO_SWIZZLE))
        {
            uint32_t i;

            bcatcstr(glsl, ".");

            for(i=0; i< 4; ++i)
            {
                if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_X)
                {
                    bcatcstr(glsl, "x");
                }
                else
                if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Y)
                {
                    bcatcstr(glsl, "y");
                }
                else
                if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Z)
                {
                    bcatcstr(glsl, "z");
                }
                else
                if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_W)
                {
                    bcatcstr(glsl, "w");
                }
            }
        }
    }
    else
    if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
    {
        bcatcstr(glsl, ".");

        if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_X)
        {
            bcatcstr(glsl, "x");
        }
        else
        if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_Y)
        {
            bcatcstr(glsl, "y");
        }
        else
        if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_Z)
        {
            bcatcstr(glsl, "z");
        }
        else
        if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_W)
        {
            bcatcstr(glsl, "w");
        }
    }

    //Component Select 1
    }
}

void TranslateDeclaration(Shader* psShader, const Declaration* psDecl)
{
    switch(psDecl->eOpcode)
    {
        case OPCODE_DCL_OUTPUT_SIV:
        {
            if(strcmp(psDecl->asOperands[0].pszSpecialName, "position") == 0)
            {
                bcatcstr(glsl, "#define ");
                TranslateOperand(&psDecl->asOperands[0]);
                bformata(glsl, " gl_Position\n");
            }
            else
            {
                bformata(glsl, "out vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

                bcatcstr(glsl, "#define ");
                TranslateOperand(&psDecl->asOperands[0]);
                bformata(glsl, " %s\n", psDecl->asOperands[0].pszSpecialName);
            }
            break;
        }
        case OPCODE_DCL_INPUT:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
            int iNumComponents = GetMaxComponentFromComponentMask(psOperand);
            bformata(glsl, "in vec%d Input%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
            break;
        }
        case OPCODE_DCL_INPUT_PS:
        {
            const Operand* psOperand = &psDecl->asOperands[0];
            int iNumComponents = GetMaxComponentFromComponentMask(psOperand);
            bformata(glsl, "in vec%d VtxOutput%d;\n", iNumComponents, psDecl->asOperands[0].ui32RegisterNumber);
            bformata(glsl, "#define Input%d VtxOutput%d\n", psDecl->asOperands[0].ui32RegisterNumber, psDecl->asOperands[0].ui32RegisterNumber);
            break;
        }
        case OPCODE_DCL_TEMPS:
        {
            uint32_t i = 0; 
            const uint32_t ui32NumTemps = psDecl->ui32NumTemps;

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
            switch(psDecl->eResourceDimension)
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
            uint32_t ui32Flags = psDecl->ui32GlobalFlags;
            
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
                psDecl->aui32WorkGroupSize[0],
                psDecl->aui32WorkGroupSize[1],
                psDecl->aui32WorkGroupSize[2]);
            break;
        }
        case OPCODE_DCL_TESS_OUTPUT_PRIMITIVE:
        {
            switch(psDecl->eTessOutPrim)
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
            switch(psDecl->eTessDomain)
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
            switch(psDecl->eTessPartitioning)
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
            switch(psDecl->ePrimitiveTopology)
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
            bformata(glsl, "layout(max_vertices = %d) out;\n", psDecl->ui32MaxOutputVertexCount);
            break;
        }
        case OPCODE_DCL_GS_INPUT_PRIMITIVE:
        {
            switch(psDecl->ePrimitiveTopology)
            {
                case PRIMITIVE_TOPOLOGY_POINTLIST:
                {
                    bcatcstr(glsl, "layout(points) in;\n");
                    break;
                }
                case PRIMITIVE_TOPOLOGY_LINELIST:
                case PRIMITIVE_TOPOLOGY_LINESTRIP:
                {
                    bcatcstr(glsl, "layout(lines) in;\n");
                    break;
                }
                case PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
                case PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
                {
                    bcatcstr(glsl, "layout(lines_adjacency) in;\n");
                    break;
                }
                case PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
                case PRIMITIVE_TOPOLOGY_TRIANGLELIST:
                {
                    bcatcstr(glsl, "layout(triangles) in;\n");
                    break;
                }
                case PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
                case PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
                {
                    bcatcstr(glsl, "layout(triangles_adjacency) in;\n");
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        default:
        {
            bformata(glsl, "/* Unhandled input declaration - opcode=0x%X */\n", psDecl->eOpcode);
            break;
        }
    }
}

void TranslateOperand(const Operand* psOperand)
{
    switch(psOperand->eModifier)
    {
        case OPERAND_MODIFIER_NONE:
        {
            break;
        }
        case OPERAND_MODIFIER_NEG:
        {
            bcatcstr(glsl, "-");
            break;
        }
        case OPERAND_MODIFIER_ABS:
        {
            bcatcstr(glsl, "abs(");
            break;
        }
        case OPERAND_MODIFIER_ABSNEG:
        {
            bcatcstr(glsl, "-abs(");
            break;
        }
    }
    switch(psOperand->eType)
    {
        case OPERAND_TYPE_IMMEDIATE32:
        {
            if(psOperand->iNumComponents == 1)
            {
                bformata(glsl, "%f",
                    psOperand->afImmediates[0]);
            }
            else
            if(psOperand->iNumComponents == 4)
            {
                bformata(glsl, "vec4(%f, %f, %f, %f)",
                    psOperand->afImmediates[0],
                    psOperand->afImmediates[1],
                    psOperand->afImmediates[2],
                    psOperand->afImmediates[3]);
            }
            break;
        }
        case OPERAND_TYPE_INPUT:
        {
            bformata(glsl, "Input%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_OUTPUT:
        {
            bformata(glsl, "Output%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_TEMP:
        {
            bformata(glsl, "Temp%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_CONSTANT_BUFFER:
        {
            bformata(glsl, "Const[%d]", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_RESOURCE:
        {
            bformata(glsl, "Resource%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_SAMPLER:
        {
            bformata(glsl, "Sampler%d", psOperand->ui32RegisterNumber);
            break;
        }
        default:
        {
            bformata(glsl, "%d %d", psOperand->eType, psOperand->ui32RegisterNumber);
            break;
        }
    }

    TranslateOperandSwizzle(psOperand);

    switch(psOperand->eModifier)
    {
        case OPERAND_MODIFIER_NONE:
        {
            break;
        }
        case OPERAND_MODIFIER_NEG:
        {
            break;
        }
        case OPERAND_MODIFIER_ABS:
        {
            bcatcstr(glsl, ")");
            break;
        }
        case OPERAND_MODIFIER_ABSNEG:
        {
            bcatcstr(glsl, ")");
            break;
        }
    }
}

void TranslateInstruction(Shader* psShader, Instruction* psInst)
{
    switch(psInst->eOpcode)
    {
        case OPCODE_MOV:
        {
            AddIndentation();
            bcatcstr(glsl, "//MOV\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = vec4(");


            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_MAD:
        {
            AddIndentation();
            bcatcstr(glsl, "//MAD\n");
            CallHLSLOpcodeFunc3("HLSL_mad", psInst);
            break;
        }
        case OPCODE_IADD:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IADD\n");
#endif
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");

            bcatcstr(glsl, "vec4(");

            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " + ");
            TranslateOperand(&psInst->asOperands[2]);

            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);

            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_ADD:
        {
            //Limit src swizzles based on dest swizzle
            //e.g. given hlsl asm: add r0.xy, v0.xyxx, l(0.100000, 0.000000, 0.000000, 0.000000)
            //the two sources must become vec2
            //Temp0.xy = Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000);
            //becomes
            //Temp0.xy = vec4(Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000)).xy;

            AddIndentation();
            bcatcstr(glsl, "//ADD\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");

            bcatcstr(glsl, "vec4(");

            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " + ");
            TranslateOperand(&psInst->asOperands[2]);

            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);

            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_OR:
        {
            /*Todo: vector version */
            AddIndentation();
            bcatcstr(glsl, "//OR\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = int(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ") | int(");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_AND:
        {
            /* Todo: vector version*/
            AddIndentation();
            bcatcstr(glsl, "//AND\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = int(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ") & int(");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_GE:
        {
            /*
                dest = vec4(greaterThanEqual(vec4(srcA), vec4(srcB));
                Caveat: The result is a boolean but HLSL asm returns 0xFFFFFFFF/0x0 instead.
             */
            AddIndentation();
            bcatcstr(glsl, "//GE\n");
            CallHLSLOpcodeFunc2("HLSL_ge", psInst);
            break;
        }
        case OPCODE_MUL:
        {
            AddIndentation();
            bcatcstr(glsl, "//MUL\n");
            CallHLSLOpcodeFunc2("HLSL_mul", psInst);
            break;
        }
        case OPCODE_DIV:
        {
            AddIndentation();
            bcatcstr(glsl, "//DIV\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " / ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_SINCOS:
        {
            AddIndentation();
            bcatcstr(glsl, "//SINCOS\n");
            if(psInst->asOperands[0].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation();
                TranslateOperand(&psInst->asOperands[0]);//Dest sin
                bcatcstr(glsl, " = sin(");
                TranslateOperand(&psInst->asOperands[2]);//angle
                bcatcstr(glsl, ");\n");
            }

            if(psInst->asOperands[1].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation();
                TranslateOperand(&psInst->asOperands[1]);//Dest cos
                bcatcstr(glsl, " = cos(");
                TranslateOperand(&psInst->asOperands[2]);//angle
                bcatcstr(glsl, ");\n");
            }
            break;
        }

        case OPCODE_DP2:
        {
            AddIndentation();
            bcatcstr(glsl, "//DP2\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ").xy);\n");
            break;
        }
        case OPCODE_DP3:
        {
            AddIndentation();
            bcatcstr(glsl, "//DP3\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ").xyz);\n");
            break;
        }
        case OPCODE_DP4:
        {
            AddIndentation();
            bcatcstr(glsl, "//DP4\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = dot(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_NE:
        {
            //Scalar version. Use any() for vector with scalar 1
            AddIndentation();
            bcatcstr(glsl, "//NE\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = (");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " != ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ") ? 1 : 0;\n");
            break;
        }
        case OPCODE_IGE:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IGE\n");
#endif
            CallHLSLOpcodeFunc2("HLSL_ige", psInst);
            break;
        }
        case OPCODE_LT:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//LT\n");
#endif
            CallHLSLOpcodeFunc2("HLSL_lt", psInst);
            break;
        }
        case OPCODE_IEQ:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IEQ\n");
#endif
            CallHLSLOpcodeFunc2("HLSL_ieq", psInst);
            break;
        }
        case OPCODE_FTOI:
        {
            // Rounding is always performed towards zero

            //Use int constructor - int(float). This drops the fractional part.
        }
        case OPCODE_MOVC:
        {
            AddIndentation();
            bcatcstr(glsl, "//MOVC\n");
            CallHLSLOpcodeFunc1("HLSL_movc", psInst);
            break;
        }
		case OPCODE_LOG:
        {
            AddIndentation();
            bcatcstr(glsl, "//LOG\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = log(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_RSQ:
        {
            AddIndentation();
            bcatcstr(glsl, "//RSQ\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = inversesqrt(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_EXP:
        {
            AddIndentation();
            bcatcstr(glsl, "//EXP\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = exp(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_SQRT:
        {
            AddIndentation();
            bcatcstr(glsl, "//SQRT\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = sqrt(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_ROUND_PI:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_PI\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ceil(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_ROUND_NI:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_NI\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = floor(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_ROUND_Z:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_Z\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = trunc(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_ROUND_NE:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_NE\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = roundEven(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_FRC:
        {
            AddIndentation();
            bcatcstr(glsl, "//FRC\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = fract(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_MAX:
        {
            AddIndentation();
            bcatcstr(glsl, "//MAX\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = max(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_MIN:
        {
            AddIndentation();
            bcatcstr(glsl, "//MIN\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = min(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_SAMPLE:
        {
            //dest, coords, tex, sampler
            AddIndentation();
            bcatcstr(glsl, "//SAMPLE\n");
            AddIndentation();//1=temp??
            TranslateOperand(&psInst->asOperands[1]);//??
            bcatcstr(glsl, " = texture2D(");

            TranslateOperand(&psInst->asOperands[3]);//resource
            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[2].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[2].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(&psInst->asOperands[2]);//in
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_SAMPLE_L:
        {
            //dest, coords, tex, sampler, lod
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//SAMPLE_L\n");
#endif
            AddIndentation();
            bcatcstr(glsl, "HLSL_sample_l");
            bcatcstr(glsl, "(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[3]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[5]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_RET:
		{
            AddIndentation();
            bcatcstr(glsl, "//RET\n");
            AddIndentation();
			bcatcstr(glsl, "return;\n");
			break;
		}
        case OPCODE_CUT:
        {
            AddIndentation();
            bcatcstr(glsl, "//CUT\n");
            AddIndentation();
			bcatcstr(glsl, "EndPrimitive();\n");
			break;
        }
        case OPCODE_EMIT:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMIT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitVertex();\n");
			break;
        }
        case OPCODE_EMITTHENCUT:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMITTHENCUT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitVertex();\nEndPrimitive();\n");
			break;
        }

        case OPCODE_CUT_STREAM:
        {
            AddIndentation();
            bcatcstr(glsl, "//CUT\n");
            AddIndentation();
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");

			break;
        }
        case OPCODE_EMIT_STREAM:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMIT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitStreamVertex(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			break;
        }
        case OPCODE_EMITTHENCUT_STREAM:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMITTHENCUT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitStreamVertex(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			break;
        }
        case OPCODE_LOOP:
        {
            AddIndentation();
            bcatcstr(glsl, "//LOOP\n");
            AddIndentation();
            bcatcstr(glsl, "while(true){\n");
            ++indent;
            break;
        }
        case OPCODE_ENDLOOP:
        {
            --indent;
            AddIndentation();
            bcatcstr(glsl, "//ENDLOOP\n");
            AddIndentation();
            bcatcstr(glsl, "}\n");
            break;
        }
        case OPCODE_BREAK:
        {
           AddIndentation();
            bcatcstr(glsl, "//BREAK\n");
            AddIndentation();
            bcatcstr(glsl, "break;\n");
            break;
        }
        case OPCODE_BREAKC:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//BREAKC\n");
#endif
            AddIndentation();
            if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
            {
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")==0){break;}\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")!=0){break;}\n");
            }
            break;
        }
        case OPCODE_IF:
        {
           AddIndentation();
            bcatcstr(glsl, "//IF\n");
            AddIndentation();
            if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
            {
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")==0){\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")!=0){\n");
            }
            ++indent;
            break;
        }
        case OPCODE_ELSE:
        {
            --indent;
           AddIndentation();
            bcatcstr(glsl, "//ELSE\n");
            AddIndentation();
            bcatcstr(glsl, "} else {\n");
            indent++;
            break;
        }
        case OPCODE_ENDIF:
        {
            --indent;
           AddIndentation();
            bcatcstr(glsl, "//ENDIF\n");
            AddIndentation();
            bcatcstr(glsl, "}\n");
            break;
        }
        default:
        {
            AddIndentation();
            bcatcstr(glsl, "//Unknown opcode\n");
#ifdef _DEBUG
            printf("Unknown opcode (toGLSL).\n");
#endif
            break;
        }
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
        default:
        {
            return "";
            break;
        }
    }
}

void TranslateToGLSL(Shader* psShader, GLLang language)
{
    uint32_t i;
    const uint32_t ui32InstCount = psShader->ui32InstCount;
    const uint32_t ui32DeclCount = psShader->ui32DeclCount;

    indent = 0;

    if(language == LANG_DEFAULT)
    {
        language = ChooseLanguage(psShader);
    }

    glsl = bfromcstralloc (1024, GetVersionString(language));

    psShader->eTargetLanguage = language;

    for(i=0; i < ui32DeclCount; ++i)
    {
        TranslateDeclaration(psShader, psShader->psDecl+i);
    }

	AddVersionDependentCode(psShader);

    AddOpcodeFuncs();

    bcatcstr(glsl, "void main()\n");
    bcatcstr(glsl, "{\n");

    indent++;

    for(i=0; i < ui32InstCount; ++i)
    {
        TranslateInstruction(psShader, psShader->psInst+i);
    }

    indent--;

    bcatcstr(glsl, "}\n");
}

void TranslateHLSLFromMem(const char* shader, GLLang language, GLSLShader* result)
{
    uint32_t* tokens;
    Shader* psShader;
    char* glslcstr = NULL;
    int GLSLShaderType = GL_FRAGMENT_SHADER_ARB;

    tokens = (uint32_t*)shader;

    psShader = DecodeDXBC(tokens);

	if(psShader)
    {
        TranslateToGLSL(psShader, language);

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

        glslcstr = bstr2cstr(glsl, '\0');

        bdestroy(glsl);

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

int TranslateHLSLFromFile(const char* filename, GLLang language, GLSLShader* result)
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

    TranslateHLSLFromMem(shader, language, result);

    free(shader);

    return 1;
}

