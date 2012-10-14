#include "toGLSLOperand.h"
#include "bstrlib.h"

#include <assert.h>
#define ASSERT(x) assert(x)

extern void AddIndentation(HLSLCrossCompilerContext* psContext);

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


void TranslateOperandSwizzle(HLSLCrossCompilerContext* psContext, const Operand* psOperand)
{
    bstring glsl = psContext->glsl;

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

void TranslateOperandIndex(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index)
{
    int i = index;
    int isGeoShader = psContext->psShader->eShaderType == GEOMETRY_SHADER ? 1 : 0;

    bstring glsl = psContext->glsl;

    ASSERT(index < psOperand->iIndexDims);

    switch(psOperand->eIndexRep[i])
    {
        case OPERAND_INDEX_IMMEDIATE32:
        {
            if(i > 0 || isGeoShader)
            {
                bformata(glsl, "[%d]", psOperand->aui32ArraySizes[i]);
            }
            else
            {
                bformata(glsl, "%d", psOperand->aui32ArraySizes[i]);
            }
            break;
        }
        case OPERAND_INDEX_RELATIVE:
        {
            bcatcstr(glsl, "[int("); //Indexes must be integral.
            TranslateOperand(psContext, psOperand->psSubOperand[i]);
            bcatcstr(glsl, ")]");
            break;
        }
        default:
        {
            break;
        }
    }
}

void TranslateSystemValueVariableName(HLSLCrossCompilerContext* psContext, const Operand* psOperand)
{
    bstring glsl = psContext->glsl;

    switch(psOperand->eType)
    {
        case OPERAND_TYPE_INPUT:
        {
            switch(psOperand->iIndexDims)
            {
                case INDEX_2D:
                {
                    if(psOperand->aui32ArraySizes[1] == 0)//Input index zero - position.
                    {
                        bcatcstr(glsl, "gl_in");
                        TranslateOperandIndex(psContext, psOperand, 0);//Vertex index
                        bcatcstr(glsl, ".gl_Position");
                    }
                    else
                    {
                        bformata(glsl, "Input%d", psOperand->aui32ArraySizes[1]);
                        TranslateOperandIndex(psContext, psOperand, 0);//Vertex index
                    }
                    break;
                }
                default:
                {
                    bformata(glsl, "Input%d", psOperand->ui32RegisterNumber);
                    break;
                }
            }
            break;
        }
        case OPERAND_TYPE_OUTPUT:
        {
            bformata(glsl, "Output%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_OUTPUT_DEPTH:
        case OPERAND_TYPE_OUTPUT_DEPTH_GREATER_EQUAL:
        case OPERAND_TYPE_OUTPUT_DEPTH_LESS_EQUAL:
        {
            bcatcstr(glsl, "gl_FragDepth");
            break;
        }
        default:
        {
            break;
        }
    }
}

void TranslateOperand(HLSLCrossCompilerContext* psContext, const Operand* psOperand)
{
    bstring glsl = psContext->glsl;

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
            switch(psOperand->iIndexDims)
            {
                case INDEX_2D:
                {
                    if(psOperand->aui32ArraySizes[1] == 0)//Input index zero - position.
                    {
                        bcatcstr(glsl, "gl_in");
                        TranslateOperandIndex(psContext, psOperand, 0);//Vertex index
                        bcatcstr(glsl, ".gl_Position");
                    }
                    else
                    {
                        bformata(glsl, "Input%d", psOperand->aui32ArraySizes[1]);
                        TranslateOperandIndex(psContext, psOperand, 0);//Vertex index
                    }
                    break;
                }
                default:
                {
                    bformata(glsl, "Input%d", psOperand->ui32RegisterNumber);
                    break;
                }
            }
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
            bformata(glsl, "Const%d[%d]", psOperand->aui32ArraySizes[0], psOperand->aui32ArraySizes[1]);
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
        case OPERAND_TYPE_OUTPUT_DEPTH:
        case OPERAND_TYPE_OUTPUT_DEPTH_GREATER_EQUAL:
        case OPERAND_TYPE_OUTPUT_DEPTH_LESS_EQUAL:
        {
            bcatcstr(glsl, "gl_FragDepth");
            break;
        }
        case OPERAND_TYPE_FUNCTION_BODY:
        {
            bformata(glsl, "Func%d", psOperand->ui32RegisterNumber);
            break;
        }
        default:
        {
            bformata(glsl, "%d %d", psOperand->eType, psOperand->ui32RegisterNumber);
            break;
        }
    }

    TranslateOperandSwizzle(psContext, psOperand);

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
