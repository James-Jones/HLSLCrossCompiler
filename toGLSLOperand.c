#include "toGLSLOperand.h"
#include "bstrlib.h"
#include "toGLSL.h"
#include "debug.h"

#include <float.h>

#ifdef _MSC_VER
#define isnan(x) _isnan(x)
#define isinf(x) (!_finite(x))
#endif

#define fpcheck(x) (isnan(x) || isinf(x))

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
		else
		//Component Swizzle
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
		{
			return 4;
		}
		else
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
		{
			return 1;
		}
    }

    return 4;
}

//e.g.
//.z = 1
//.x = 1
//.yw = 2
uint32_t GetNumSwizzleElements(HLSLCrossCompilerContext* psContext, const Operand* psOperand)
{
    bstring glsl = psContext->glsl;
	uint32_t count = 0;

	switch(psOperand->eType)
	{
		case OPERAND_TYPE_IMMEDIATE32:
		case OPERAND_TYPE_IMMEDIATE64:
		case OPERAND_TYPE_OUTPUT_DEPTH_GREATER_EQUAL:
		case OPERAND_TYPE_OUTPUT_DEPTH_LESS_EQUAL:
		case OPERAND_TYPE_OUTPUT_DEPTH:
		{
			return psOperand->iNumComponents;
		}
		default:
		{
			break;
		}
	}

    if(psOperand->iWriteMaskEnabled &&
       psOperand->iNumComponents == 4)
    {
		//Comonent Mask
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
		{
			if(psOperand->ui32CompMask != 0 && psOperand->ui32CompMask != (OPERAND_4_COMPONENT_MASK_X|OPERAND_4_COMPONENT_MASK_Y|OPERAND_4_COMPONENT_MASK_Z|OPERAND_4_COMPONENT_MASK_W))
			{
				if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_X)
				{
					count++;
				}
				if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Y)
				{
					count++;
				}
				if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Z)
				{
					count++;
				}
				if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_W)
				{
					count++;
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

				for(i=0; i< 4; ++i)
				{
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_X)
					{
						count++;
					}
					else
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Y)
					{
						count++;
					}
					else
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Z)
					{
						count++;
					}
					else
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_W)
					{
						count++;
					}
				}
			}
		}
		else
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
		{
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_X)
			{
				count++;
			}
			else
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_Y)
			{
				count++;
			}
			else
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_Z)
			{
				count++;
			}
			else
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_W)
			{
				count++;
			}
		}

		//Component Select 1
	}

    if(!count)
    {
        return psOperand->iNumComponents;
    }

	return count;
}

void AddSwizzleUsingElementCount(HLSLCrossCompilerContext* psContext, uint32_t count)
{
	bstring glsl = psContext->glsl;
	if(count)
	{
		bcatcstr(glsl, ".");
		bcatcstr(glsl, "x");
		count--;
	}
	if(count)
	{
		bcatcstr(glsl, "y");
		count--;
	}
	if(count)
	{
		bcatcstr(glsl, "z");
		count--;
	}
	if(count)
	{
		bcatcstr(glsl, "w");
		count--;
	}
}

static uint32_t ConvertOperandSwizzleToComponentMask(const Operand* psOperand)
{
    uint32_t mask = 0;

    if(psOperand->iWriteMaskEnabled &&
       psOperand->iNumComponents == 4)
    {
		//Comonent Mask
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
		{
            mask = psOperand->ui32CompMask;
		}
		else
		//Component Swizzle
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
		{
			if(psOperand->ui32Swizzle != (NO_SWIZZLE))
			{
				uint32_t i;

				for(i=0; i< 4; ++i)
				{
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_X)
					{
						mask |= OPERAND_4_COMPONENT_MASK_X;
					}
					else
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Y)
					{
						mask |= OPERAND_4_COMPONENT_MASK_Y;
					}
					else
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Z)
					{
						mask |= OPERAND_4_COMPONENT_MASK_Z;
					}
					else
					if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_W)
					{
						mask |= OPERAND_4_COMPONENT_MASK_W;
					}
				}
			}
		}
		else
		if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
		{
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_X)
			{
				mask |= OPERAND_4_COMPONENT_MASK_X;
			}
			else
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_Y)
			{
				mask |= OPERAND_4_COMPONENT_MASK_Y;
			}
			else
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_Z)
			{
				mask |= OPERAND_4_COMPONENT_MASK_Z;
			}
			else
			if(psOperand->aui32Swizzle[0] == OPERAND_4_COMPONENT_W)
			{
				mask |= OPERAND_4_COMPONENT_MASK_W;
			}
		}

		//Component Select 1
	}

    return mask;
}

//Non-zero means the components overlap
int CompareOperandSwizzles(const Operand* psOperandA, const Operand* psOperandB)
{
    uint32_t maskA = ConvertOperandSwizzleToComponentMask(psOperandA);
    uint32_t maskB = ConvertOperandSwizzleToComponentMask(psOperandB);

    return maskA & maskB;
}


void TranslateOperandSwizzle(HLSLCrossCompilerContext* psContext, const Operand* psOperand)
{
    bstring glsl = psContext->glsl;

	if(psOperand->eType == OPERAND_TYPE_OUTPUT)
	{
		if(psContext->psShader->abScalarOutput[psOperand->ui32RegisterNumber])
		{
			return;
		}
	}
	if(psOperand->eType == OPERAND_TYPE_INPUT)
	{
		if(psContext->psShader->abScalarInput[psOperand->ui32RegisterNumber])
		{
			return;
		}
	}

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
            TranslateOperand(psContext, psOperand->psSubOperand[i], TO_FLAG_NONE);
            bcatcstr(glsl, ")]");
            break;
        }
        case OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE:
        {
            bcatcstr(glsl, "[int("); //Indexes must be integral.
            TranslateOperand(psContext, psOperand->psSubOperand[i], TO_FLAG_NONE);
            bformata(glsl, ") + %d]", psOperand->aui32ArraySizes[i]);
            break;
        }
        default:
        {
            break;
        }
    }
}

void TranslateOperandIndexMAD(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index, uint32_t multiply, uint32_t add)
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
                bformata(glsl, "[%d*%d+%d]", psOperand->aui32ArraySizes[i], multiply, add);
            }
            else
            {
                bformata(glsl, "%d*%d+%d", psOperand->aui32ArraySizes[i], multiply, add);
            }
            break;
        }
        case OPERAND_INDEX_RELATIVE:
        {
            bcatcstr(glsl, "[int("); //Indexes must be integral.
            TranslateOperand(psContext, psOperand->psSubOperand[i], TO_FLAG_NONE);
            bformata(glsl, ")*%d+%d]", multiply, add);
            break;
        }
        case OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE:
        {
            bcatcstr(glsl, "[(int("); //Indexes must be integral.
            TranslateOperand(psContext, psOperand->psSubOperand[i], TO_FLAG_NONE);
            bformata(glsl, ") + %d)*%d+%d]", psOperand->aui32ArraySizes[i], multiply, add);
            break;
        }
        default:
        {
            break;
        }
    }
}

//Returns 1 if the operand has a special name.
static int TranslateSpecialInputName(HLSLCrossCompilerContext* psContext, const Operand* psOperand)
{
    bstring glsl = psContext->glsl;
    const SPECIAL_NAME eSpecialName = psContext->psShader->aSpecialInputs[psOperand->ui32RegisterNumber];

    switch(eSpecialName)
    {
        case NAME_IS_FRONT_FACE:
        {
            /*
                Cast to int used because
                if(gl_FrontFacing != 0) failed to compiled on Intel HD 4000.
                Suggests no implicit conversion for bool<->int.
            */
            bcatcstr(glsl, "int(gl_FrontFacing)");
            return 1;
        }
        case NAME_PRIMITIVE_ID:
        {
            bcatcstr(glsl, "gl_PrimitiveID");
            return 1;
        }
        case NAME_SAMPLE_INDEX:
        {
            bcatcstr(glsl, "gl_SampleID");
            return 1;
        }
        case NAME_INSTANCE_ID:
        {
            bcatcstr(glsl, "gl_InstanceID");
            return 1;
        }
        case NAME_VERTEX_ID:
        {
            bcatcstr(glsl, "gl_VertexID");
            return 1;
        }
        case NAME_VIEWPORT_ARRAY_INDEX:
        {
            bcatcstr(glsl, "gl_ViewportIndex");
            return 1;
        }
        case NAME_RENDER_TARGET_ARRAY_INDEX:
        {
            /*
                HLSL allows .x on scalars. Upgrade scalar
                system values to vec1 so .x works. Even when
                GLSL allows a vec1, this will still be needed for
                backwards compatiblility.
            */
            bcatcstr(glsl, "vec1(gl_Layer)");
            return 1;
        }
        case NAME_CLIP_DISTANCE:
        {
            bcatcstr(glsl, "gl_ClipDistance");
            return 1;
        }
        case NAME_POSITION:
        {
            bcatcstr(glsl, "gl_Position");
            return 1;
        }
    }
    return 0;
}

static void TranslateVariableName(HLSLCrossCompilerContext* psContext, const Operand* psOperand, uint32_t ui32TOFlag, uint32_t* pui32IgnoreSwizzle)
{
    bstring glsl = psContext->glsl;

    *pui32IgnoreSwizzle = 0;

    switch(psOperand->eType)
    {
        case OPERAND_TYPE_IMMEDIATE32:
        {
            if(psOperand->iNumComponents == 1)
            {
				if((ui32TOFlag & TO_FLAG_INTEGER) || psOperand->iIntegerImmediate || fpcheck(psOperand->afImmediates[0]))
				{
					bformata(glsl, "%d",
						*((int*)(&psOperand->afImmediates[0])));
				}
				else
				{
					bformata(glsl, "%f",
                    psOperand->afImmediates[0]);
				}
            }
            else
            if(psOperand->iNumComponents == 4)
            {
                if((ui32TOFlag & TO_FLAG_INTEGER) ||
                    psOperand->iIntegerImmediate ||
                    fpcheck(psOperand->afImmediates[0]) ||
                    fpcheck(psOperand->afImmediates[1]) ||
                    fpcheck(psOperand->afImmediates[2]) ||
                    fpcheck(psOperand->afImmediates[3]))
                {
                    bformata(glsl, "vec4(%d, %d, %d, %d)",
                        *(int*)&psOperand->afImmediates[0],
                        *(int*)&psOperand->afImmediates[1],
                        *(int*)&psOperand->afImmediates[2],
                        *(int*)&psOperand->afImmediates[3]);
                }
                else
                {
                    bformata(glsl, "vec4(%f, %f, %f, %f)",
                        psOperand->afImmediates[0],
                        psOperand->afImmediates[1],
                        psOperand->afImmediates[2],
                        psOperand->afImmediates[3]);
                }
            }
            break;
        }
        case OPERAND_TYPE_INPUT:
        {
            if(TranslateSpecialInputName(psContext, psOperand))
            {
                //All of the special names are scalar at the moment.
                //Most versions of GLSL do not allow .x on scalar, unlike HLSL bytecode.
                *pui32IgnoreSwizzle = 1;
            }
            else
            {
                switch(psOperand->iIndexDims)
                {
                    case INDEX_2D:
                    {
                        if(psOperand->aui32ArraySizes[1] == 0)//Input index zero - position.
                        {
                            bcatcstr(glsl, "gl_in");
                            TranslateOperandIndex(psContext, psOperand, TO_FLAG_NONE);//Vertex index
                            bcatcstr(glsl, ".gl_Position");
                        }
                        else
                        {
                            bformata(glsl, "Input%d", psOperand->aui32ArraySizes[1]);
                            TranslateOperandIndex(psContext, psOperand, TO_FLAG_NONE);//Vertex index
                        }
                        break;
                    }
                    default:
                    {
                        if(psOperand->eIndexRep[0] == OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE)
                        {
                            bformata(glsl, "Input%d[int(", psOperand->ui32RegisterNumber);
                            TranslateOperand(psContext, psOperand->psSubOperand[0], TO_FLAG_NONE);
                            bcatcstr(glsl, ")]");
                        }
                        else
                        {
                            if(psContext->psShader->aIndexedInput[psOperand->ui32RegisterNumber] != 0)
                            {
                                const uint32_t parentIndex = psContext->psShader->aIndexedInputParents[psOperand->ui32RegisterNumber];
                                bformata(glsl, "Input%d[%d]", parentIndex,
                                    psOperand->ui32RegisterNumber - parentIndex);
                            }
                            else
                            {
                                bformata(glsl, "Input%d", psOperand->ui32RegisterNumber);
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        case OPERAND_TYPE_OUTPUT:
        {
            bformata(glsl, "Output%d", psOperand->ui32RegisterNumber);
            if(psOperand->psSubOperand[0])
            {
                bcatcstr(glsl, "[int("); //Indexes must be integral.
                TranslateOperand(psContext, psOperand->psSubOperand[0], TO_FLAG_NONE);
                bcatcstr(glsl, ")]");
            }
            break;
        }
        case OPERAND_TYPE_OUTPUT_DEPTH:
        case OPERAND_TYPE_OUTPUT_DEPTH_GREATER_EQUAL:
        case OPERAND_TYPE_OUTPUT_DEPTH_LESS_EQUAL:
        {
            bcatcstr(glsl, "gl_FragDepth");
            break;
        }
        case OPERAND_TYPE_TEMP:
        {
            bformata(glsl, "Temp%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_CONSTANT_BUFFER:
        {
            const char* StageName = "VS";
            ConstantBuffer* psCBuf = NULL;
            GetConstantBufferFromBindingPoint(psOperand->aui32ArraySizes[0], &psContext->psShader->sInfo, &psCBuf);

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
                char* pszContBuffName;

                pszContBuffName = psCBuf->Name;
                
                if(psCBuf->Name[0] == '$')//$Global or $Param
                    pszContBuffName++;

                ASSERT(psOperand->aui32ArraySizes[1] < psCBuf->ui32NumVars);
                
                bformata(glsl, "%s%s.%s", pszContBuffName, StageName, psCBuf->asVars[psOperand->aui32ArraySizes[1]].Name);
            }
#else
			if(psContext->flags & HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT)
			{
                if((psCBuf->Name[0] == '$') && (psContext->flags & HLSLCC_FLAG_GLOBAL_CONSTS_NEVER_IN_UBO))
                {
                    bformata(glsl, "Globals%s[%d]", StageName, psOperand->aui32ArraySizes[1]);
                }
                else
                {
				    //Each uniform block is given the HLSL consant buffer name.
				    //Within each uniform block is a constant array named ConstN
				    bformata(glsl, "Const%d[%d]", psOperand->aui32ArraySizes[0], psOperand->aui32ArraySizes[1]);
                }
			}
			else
			{
				//$Globals.
				if(psCBuf->Name[0] == '$')
				{
					bformata(glsl, "Globals%s[%d]", StageName, psOperand->aui32ArraySizes[1]);
				}
				else
				{
					bformata(glsl, "%s%s[%d]", psCBuf->Name, StageName, psOperand->aui32ArraySizes[1]);
				}
			}
#endif
            break;
        }
        case OPERAND_TYPE_RESOURCE:
        {
            TextureName(psContext, psOperand->ui32RegisterNumber, 0);
            break;
        }
        case OPERAND_TYPE_SAMPLER:
        {
            bformata(glsl, "Sampler%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_FUNCTION_BODY:
        {
            const uint32_t ui32FuncBody = psOperand->ui32RegisterNumber;
            const uint32_t ui32FuncTable = psContext->psShader->aui32FuncBodyToFuncTable[ui32FuncBody];
            //const uint32_t ui32FuncPointer = psContext->psShader->aui32FuncTableToFuncPointer[ui32FuncTable];
            const uint32_t ui32ClassType = psContext->psShader->sInfo.aui32TableIDToTypeID[ui32FuncTable];
            const char* ClassTypeName = &psContext->psShader->sInfo.psClassTypes[ui32ClassType].Name[0];
            const uint32_t ui32UniqueClassFuncIndex = psContext->psShader->ui32NextClassFuncName[ui32ClassType]++;

            bformata(glsl, "%s_Func%d", ClassTypeName, ui32UniqueClassFuncIndex);
            break;
        }
		case OPERAND_TYPE_INPUT_FORK_INSTANCE_ID:
		{
			bcatcstr(glsl, "forkInstanceID");
            *pui32IgnoreSwizzle = 1;
			return;
		}
		case OPERAND_TYPE_IMMEDIATE_CONSTANT_BUFFER:
		{
            bcatcstr(glsl, "immediateConstBufferF");

            if(psOperand->psSubOperand[0])
            {
                bcatcstr(glsl, "(int("); //Indexes must be integral.
                TranslateOperand(psContext, psOperand->psSubOperand[0], TO_FLAG_NONE);
                bcatcstr(glsl, "))");
            }
			break;
		}
		case OPERAND_TYPE_INPUT_DOMAIN_POINT:
		{
			bcatcstr(glsl, "gl_TessCoord");
			break;
		}
		case OPERAND_TYPE_INPUT_CONTROL_POINT:
		{
			if(psOperand->aui32ArraySizes[1] == 0)//Input index zero - position.
			{
				bformata(glsl, "gl_in[%d].gl_Position", psOperand->aui32ArraySizes[0]);
			}
            else
            {
                bformata(glsl, "Input%d[%d]", psOperand->aui32ArraySizes[1], psOperand->aui32ArraySizes[0]);
            }
            break;
		}
		case OPERAND_TYPE_NULL:
		{
			// Null register, used to discard results of operations
			bcatcstr(glsl, "//null");
			break;
		}
        case OPERAND_TYPE_OUTPUT_CONTROL_POINT_ID:
        {
            bcatcstr(glsl, "gl_InvocationID");
            *pui32IgnoreSwizzle = 1;
            break;
        }
        case OPERAND_TYPE_OUTPUT_COVERAGE_MASK:
        {
            bcatcstr(glsl, "gl_SampleMask[0]");
            *pui32IgnoreSwizzle = 1;
            break;
        }
        case OPERAND_TYPE_INPUT_COVERAGE_MASK:
        {
            bcatcstr(glsl, "gl_SampleMaskIn[0]");
            //Skip swizzle on scalar types.
            *pui32IgnoreSwizzle = 1;
            break;
        }
        default:
        {
            ASSERT(0);
            break;
        }
    }
}

void TranslateOperand(HLSLCrossCompilerContext* psContext, const Operand* psOperand, uint32_t ui32TOFlag)
{
    bstring glsl = psContext->glsl;
    uint32_t ui32IgnoreSwizzle = 0;

    if(ui32TOFlag & TO_FLAG_NAME_ONLY)
    {
        TranslateVariableName(psContext, psOperand, ui32TOFlag, &ui32IgnoreSwizzle);
        return;
    }

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

    TranslateVariableName(psContext, psOperand, ui32TOFlag, &ui32IgnoreSwizzle);

    if(!ui32IgnoreSwizzle)
    {
        TranslateOperandSwizzle(psContext, psOperand);
    }

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

void TextureName(HLSLCrossCompilerContext* psContext, const uint32_t ui32RegisterNumber, const int bZCompare)
{
    bstring glsl = psContext->glsl;
    ResourceBinding* psBinding = 0;
	int found;
    found = GetResourceFromBindingPoint(RTYPE_TEXTURE, ui32RegisterNumber, &psContext->psShader->sInfo, &psBinding);

    if(bZCompare)
    {
        bcatcstr(glsl, "hlslcc_zcmp_");
    }

	if(found)
	{
        int i = 0;
        char name[MAX_REFLECT_STRING_LENGTH];
		uint32_t ui32ArrayOffset = ui32RegisterNumber - psBinding->ui32BindPoint;

        while(psBinding->Name[i] != '\0' && i < (MAX_REFLECT_STRING_LENGTH-1))
        {
            name[i] = psBinding->Name[i];

            //array syntax [X] becomes _0_
            //Otherwise declarations could end up as:
            //uniform sampler2D SomeTextures[0];
            //uniform sampler2D SomeTextures[1];
            if(name[i] == '[' || name[i] == ']')
                name[i] = '_';

            ++i;
        }

        name[i] = '\0';

		if(ui32ArrayOffset)
		{
			bformata(glsl, "%s%d", name, ui32ArrayOffset);
		}
		else
		{
			bformata(glsl, "%s", name);
		}
	}
	else
	{
		bformata(glsl, "UnknownResource%d", ui32RegisterNumber);
	}
}
