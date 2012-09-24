#include "tokens.h"
#include "structs.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"
#include "hlsl_opcode_funcs_glsl.h"

#include <assert.h>

#define ASSERT(x) assert(x)

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
                    bcatcstr(glsl, "uniform samplerCuubeArray ");
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
            CallHLSLOpcodeFunc3("mad", psInst);
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
            AddIndentation();

            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = vec4(greaterThanEqual(vec4(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, "), vec4(");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ")))");
            TranslateOperandSwizzle(&psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_MUL:
        {
            AddIndentation();
            bcatcstr(glsl, "//MUL\n");
            CallHLSLOpcodeFunc2("mul", psInst);
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
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = greaterThanEqual(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_LT:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//LT\n");
#endif
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = lessThan(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_IEQ:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IEQ\n");
#endif
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = equal(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
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
            CallHLSLOpcodeFunc1("movc", psInst);
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
            AddIndentation();//1=temp??
            TranslateOperand(&psInst->asOperands[1]);//??
            bcatcstr(glsl, " = texture2DLod(");

            TranslateOperand(&psInst->asOperands[3]);//resource
            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[2].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[2].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(&psInst->asOperands[2]);//in
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

void TranslateToGLSL(Shader* psShader)
{
    uint32_t i;
    const uint32_t ui32InstCount = psShader->ui32InstCount;
    const uint32_t ui32DeclCount = psShader->ui32DeclCount;

    indent = 0;

	if(psShader->ui32MajorVersion == 5)
	{
        //glsl = bfromcstralloc (1024, "#version 420\n");
        glsl = bfromcstralloc (1024, "#version 330\n");
	}
	else
	if(psShader->ui32MajorVersion == 4)
	{
        glsl = bfromcstralloc (1024, "#version 330\n");
	}

    for(i=0; i < ui32DeclCount; ++i)
    {
        TranslateDeclaration(psShader, psShader->psDecl+i);
    }

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

#define VALIDATE_OUTPUT

#if defined(VALIDATE_OUTPUT) && defined(_WIN32)
#if defined(_WIN32)
#include <windows.h>
#include <gl/GL.h>

 #pragma comment(lib, "opengl32.lib")

	typedef char GLcharARB;		/* native character */
	typedef unsigned int GLhandleARB;	/* shader object handle */
#define GL_VERTEX_SHADER_ARB              0x8B31
#define GL_FRAGMENT_SHADER_ARB            0x8B30
#define GL_OBJECT_COMPILE_STATUS_ARB      0x8B81
#define GL_OBJECT_LINK_STATUS_ARB         0x8B82
	typedef void (WINAPI * PFNGLDELETEOBJECTARBPROC) (GLhandleARB obj);
	typedef GLhandleARB (WINAPI * PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
	typedef void (WINAPI * PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, const GLcharARB* *string, const GLint *length);
	typedef void (WINAPI * PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
	typedef void (WINAPI * PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
	typedef void (WINAPI * PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint *params);
	typedef GLhandleARB (WINAPI * PFNGLCREATEPROGRAMOBJECTARBPROC) (void);
	typedef void (WINAPI * PFNGLATTACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB obj);
	typedef void (WINAPI * PFNGLLINKPROGRAMARBPROC) (GLhandleARB programObj);
	typedef void (WINAPI * PFNGLUSEPROGRAMOBJECTARBPROC) (GLhandleARB programObj);
    //typedef void (WINAPI * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* param);
    typedef void (WINAPI * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei* length, GLcharARB* infoLog);

	static PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
	static PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
	static PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
	static PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
	static PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
	static PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
	static PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
	static PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
	static PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
	static PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
    //static PFNGLGETSHADERIVPROC glGetShaderiv;
    static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

void InitOpenGL()
{
    HGLRC rc;

	// setup minimal required GL
	HWND wnd = CreateWindowA(
							 "STATIC",
							 "GL",
							 WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
							 0, 0, 16, 16,
							 NULL, NULL,
							 GetModuleHandle(NULL), NULL );
	HDC dc = GetDC( wnd );
	
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA, 32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		16, 0,
		0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};
	
	int fmt = ChoosePixelFormat( dc, &pfd );
	SetPixelFormat( dc, fmt, &pfd );
	
	rc = wglCreateContext( dc );
	wglMakeCurrent( dc, rc );

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if(wglCreateContextAttribsARB)
    {
        const int OpenGLContextAttribs [] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    #if defined(_DEBUG)
            //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
    #else
            //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    #endif
            //WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0, 0
        };

        const HGLRC OpenGLContext = wglCreateContextAttribsARB( dc, 0, OpenGLContextAttribs );

        wglMakeCurrent(dc, OpenGLContext);

        wglDeleteContext(rc);

        rc = OpenGLContext;
    }

    glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)wglGetProcAddress("glDeleteObjectARB");
    glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
    glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB");
    glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB");
    glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
    glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
    glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)wglGetProcAddress("glCreateProgramObjectARB");
    glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)wglGetProcAddress("glAttachObjectARB");
    glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB");
    glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)wglGetProcAddress("glUseProgramObjectARB");
    //glGetShaderiv = (PFNGLGETSHADERIVPROC)("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)("glGetShaderInfoLog");
}
#endif

int TryCompileShader(SHADER_TYPE eShaderType, char* shader)
{
    GLint iCompileStatus;
    GLuint hShader;
    GLenum eGLSLShaderType = GL_FRAGMENT_SHADER_ARB;

    switch(eShaderType)
    {
        case VERTEX_SHADER:
        {
            eGLSLShaderType = GL_VERTEX_SHADER_ARB;
            break;
        }
        default:
        {
            break;
        }
    }

    InitOpenGL();

    hShader = glCreateShaderObjectARB(eGLSLShaderType);
    glShaderSourceARB(hShader, 1, (const char **)&shader, NULL);

    glCompileShaderARB(hShader);

    /* Check it compiled OK */
    glGetObjectParameterivARB (hShader, GL_OBJECT_COMPILE_STATUS_ARB, &iCompileStatus);
    //glGetShaderiv(hShader, GL_COMPILE_STATUS, &iCompileStatus); 

    if (iCompileStatus != GL_TRUE)
    {
        FILE* errorFile;
        GLint iInfoLogLength = 0;
        char pszInfoLog[1024];

        printf("Error: Failed to compile GLSL shader\n");

		//char log[4096];
		//GLsizei logLength;
		glGetInfoLogARB (hShader, sizeof(pszInfoLog), &iInfoLogLength, pszInfoLog);

        //glGetShaderInfoLog(hShader, 1024, &iInfoLogLength, pszInfoLog);
        printf(pszInfoLog);

        //Dump to file
        errorFile = fopen("compileErrors.txt", "w");
        fprintf(errorFile, pszInfoLog);
        fclose(errorFile);

        return 0;
    }

    printf("Shader compiled successfully\n");

    return 1;
}
#endif

void TranslateHLSLFromFile(const char* filename, char** result)
{
}

void main(int argc, char** argv)
{
    FILE* shaderFile;
    FILE* outputFile;
    int length;
    int readLength;
    char* shader;
    uint32_t* tokens;
    Shader* psShader;
    char* glslcstr;

    if(argc < 2 || !(shaderFile = fopen(argv[1], "rb")))
    {
        printf("Bad args. Supply a valid shader path, optionaly followed by the output path\n");
        return;
    }

    fseek(shaderFile, 0, SEEK_END);
    length = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET);

    shader = (char*)malloc(length+1);

    readLength = fread(shader, 1, length, shaderFile);

    fclose(shaderFile);
    shaderFile = 0;

    shader[readLength] = '\0';

    tokens = (uint32_t*)shader;

    psShader = DecodeDXBC(tokens);

	if(psShader)
    {
        TranslateToGLSL(psShader);

        glslcstr = bstr2cstr(glsl, '\0');

        if(argc > 2)
        {
            //Dump to file
            outputFile = fopen(argv[2], "w");
            fprintf(outputFile, glslcstr);
            fclose(outputFile);
        }

#if defined(VALIDATE_OUTPUT)
        TryCompileShader(psShader->eShaderType, glslcstr);
#endif

        bcstrfree(glslcstr);
        bdestroy(glsl);

        free(psShader->psDecl);
        free(psShader->psInst);
        free(psShader);
    }

    free(shader);
    shader = 0;
    tokens = 0;
}
