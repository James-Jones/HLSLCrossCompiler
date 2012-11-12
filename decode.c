#include "tokens.h"
#include "structs.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "reflect.h"
#include "assert.h"

#define FOURCC(a, b, c, d) ((uint32_t)(uint8_t)(a) | ((uint32_t)(uint8_t)(b) << 8) | ((uint32_t)(uint8_t)(c) << 16) | ((uint32_t)(uint8_t)(d) << 24 ))
const uint32_t FOURCC_DXBC = FOURCC('D', 'X', 'B', 'C');
const uint32_t FOURCC_SHDR = FOURCC('S', 'H', 'D', 'R');
const uint32_t FOURCC_SHEX = FOURCC('S', 'H', 'E', 'X');
const uint32_t FOURCC_RDEF = FOURCC('R', 'D', 'E', 'F');

#ifdef _DEBUG
#define ASSERT(expr) assert(expr)
#else
#define ASSERT(expr)
#endif

typedef struct DXBCContainerHeaderTAG
{
	unsigned fourcc;
	uint32_t unk[4];
	uint32_t one;
	uint32_t totalSize;
	uint32_t chunkCount;
} DXBCContainerHeader;

typedef struct DXBCChunkHeaderTAG
{
	unsigned fourcc;
	unsigned size;
} DXBCChunkHeader;

#ifdef _DEBUG
static uint64_t operandID = 0;
static uint64_t instructionID = 0;
#endif

void DecodeNameToken(const uint32_t* pui32NameToken, Operand* psOperand)
{
    const size_t MAX_BUFFER_SIZE = sizeof(psOperand->pszSpecialName);
    psOperand->eSpecialName = DecodeOperandSpecialName(*pui32NameToken);
	switch(psOperand->eSpecialName)
	{
        case NAME_UNDEFINED:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "undefined");
            break;
        }
        case NAME_POSITION:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "position");
            break;
        }
        case NAME_CLIP_DISTANCE:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "clipDistance");
            break;
        }
        case NAME_CULL_DISTANCE:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "cullDistance");
            break;
        }
        case NAME_RENDER_TARGET_ARRAY_INDEX:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "renderTargetArrayIndex");
            break;
        }
        case NAME_VIEWPORT_ARRAY_INDEX:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "viewportArrayIndex");
            break;
        }
        case NAME_VERTEX_ID:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "vertexID");
            break;
        }
        case NAME_PRIMITIVE_ID:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "primitiveID");
            break;
        }
        case NAME_INSTANCE_ID:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "instanceID");
            break;
        }
        case NAME_IS_FRONT_FACE:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "isFrontFace");
            break;
        }
        case NAME_SAMPLE_INDEX:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "sampleIndex");
            break;
        }
        //For the quadrilateral domain, there are 6 factors (4 sides, 2 inner).
		case NAME_FINAL_QUAD_U_EQ_0_EDGE_TESSFACTOR:
		case NAME_FINAL_QUAD_V_EQ_0_EDGE_TESSFACTOR: 
		case NAME_FINAL_QUAD_U_EQ_1_EDGE_TESSFACTOR: 
		case NAME_FINAL_QUAD_V_EQ_1_EDGE_TESSFACTOR:
		case NAME_FINAL_QUAD_U_INSIDE_TESSFACTOR:
		case NAME_FINAL_QUAD_V_INSIDE_TESSFACTOR:

        //For the triangular domain, there are 4 factors (3 sides, 1 inner)
		case NAME_FINAL_TRI_U_EQ_0_EDGE_TESSFACTOR:
		case NAME_FINAL_TRI_V_EQ_0_EDGE_TESSFACTOR:
		case NAME_FINAL_TRI_W_EQ_0_EDGE_TESSFACTOR:
		case NAME_FINAL_TRI_INSIDE_TESSFACTOR:

        //For the isoline domain, there are 2 factors (detail and density).
		case NAME_FINAL_LINE_DETAIL_TESSFACTOR:
		case NAME_FINAL_LINE_DENSITY_TESSFACTOR:
        {
            sprintf_s(psOperand->pszSpecialName, MAX_BUFFER_SIZE, "tessFactor");
            break;
        }
        default:
        {
            ASSERT(0);
            break;
        }
    }

    return;
}

uint32_t DecodeOperand (const uint32_t *pui32Tokens, Operand* psOperand)
{
    int i;
	uint32_t ui32NumTokens = 1;
    OPERAND_NUM_COMPONENTS eNumComponents;

#ifdef _DEBUG
    psOperand->id = operandID++;
#endif

    //Some defaults
    psOperand->iWriteMaskEnabled = 1;
    psOperand->iGSInput = 0;

    psOperand->iExtended = DecodeIsOperandExtended(*pui32Tokens);


    psOperand->eModifier = OPERAND_MODIFIER_NONE;
    psOperand->psSubOperand[0] = 0;
    psOperand->psSubOperand[1] = 0;
    psOperand->psSubOperand[2] = 0;

	/* Check if this instruction is extended.  If it is,
	 * we need to print the information first */
	if (psOperand->iExtended)
	{
		/* OperandToken1 is the second token */
		ui32NumTokens++;

        if(DecodeExtendedOperandType(pui32Tokens[1]) == EXTENDED_OPERAND_MODIFIER)
        {
            psOperand->eModifier = DecodeExtendedOperandModifier(pui32Tokens[1]);
        }

	}

	psOperand->iIndexDims = DecodeOperandIndexDimension(*pui32Tokens);
    psOperand->eType = DecodeOperandType(*pui32Tokens);

    if(psOperand->eType == OPERAND_TYPE_SAMPLER ||
       psOperand->eType == OPERAND_TYPE_RESOURCE)
    {
        psOperand->iWriteMaskEnabled = 0;
    }

    psOperand->ui32RegisterNumber = 0;

    eNumComponents = DecodeOperandNumComponents(*pui32Tokens);

    switch(eNumComponents)
    {
        case OPERAND_1_COMPONENT:
        {
            psOperand->iNumComponents = 1;
            break;
        }
        case OPERAND_4_COMPONENT:
        {
            psOperand->iNumComponents = 4;
            break;
        }
        default:
        {
            psOperand->iNumComponents = 0;
            break;
        }
    }

    if(psOperand->iWriteMaskEnabled &&
       psOperand->iNumComponents == 4)
    {
        psOperand->eSelMode = DecodeOperand4CompSelMode(*pui32Tokens);

        if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
        {
            psOperand->ui32CompMask = DecodeOperand4CompMask(*pui32Tokens);
        }
        else
        if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
        {
            psOperand->ui32Swizzle = DecodeOperand4CompSwizzle(*pui32Tokens);

            if(psOperand->ui32Swizzle != NO_SWIZZLE)
            {
                psOperand->aui32Swizzle[0] = DecodeOperand4CompSwizzleSource(*pui32Tokens, 0);
                psOperand->aui32Swizzle[1] = DecodeOperand4CompSwizzleSource(*pui32Tokens, 1);
                psOperand->aui32Swizzle[2] = DecodeOperand4CompSwizzleSource(*pui32Tokens, 2);
                psOperand->aui32Swizzle[3] = DecodeOperand4CompSwizzleSource(*pui32Tokens, 3);
            }
        }
        else
        if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
        {
            psOperand->aui32Swizzle[0] = DecodeOperand4CompSel1(*pui32Tokens);
        }
    }

	//Set externally to this function based on the instruction opcode.
	psOperand->iIntegerImmediate = 0;

    if(psOperand->eType == OPERAND_TYPE_IMMEDIATE32)
    {
        for(i=0; i< psOperand->iNumComponents; ++i)
        {
            psOperand->afImmediates[i] = *((float*)(&pui32Tokens[ui32NumTokens]));
            ui32NumTokens ++;
        }
    }

    for(i=0; i <psOperand->iIndexDims; ++i)
    {
        OPERAND_INDEX_REPRESENTATION eRep = DecodeOperandIndexRepresentation(i ,*pui32Tokens);

        psOperand->eIndexRep[i] = eRep;

        psOperand->aui32ArraySizes[i] = 0;
        psOperand->ui32RegisterNumber = 0;

        switch(eRep)
        {
            case OPERAND_INDEX_IMMEDIATE32:
            {
                psOperand->ui32RegisterNumber = *(pui32Tokens+ui32NumTokens);
                psOperand->aui32ArraySizes[i] = psOperand->ui32RegisterNumber;
                break;
            }
            case OPERAND_INDEX_RELATIVE:
            {
                psOperand->psSubOperand[i] = malloc(sizeof(Operand));
                    DecodeOperand(pui32Tokens+ui32NumTokens, psOperand->psSubOperand[i]);

                    ui32NumTokens++;
                break;
            }
			case OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE:
			{
                psOperand->ui32RegisterNumber = *(pui32Tokens+ui32NumTokens);
                psOperand->aui32ArraySizes[i] = psOperand->ui32RegisterNumber;

                ui32NumTokens++;

                psOperand->psSubOperand[i] = malloc(sizeof(Operand));
                    DecodeOperand(pui32Tokens+ui32NumTokens, psOperand->psSubOperand[i]);

				ui32NumTokens++;
				break;
			}
            default:
            {
                ASSERT(0);
                break;
            }
        }

        ui32NumTokens++;
    }

    psOperand->pszSpecialName[0] ='\0';

    //psOperand->ui32RegisterNumber = pui32Tokens[0] & 0x3FF;

    return ui32NumTokens;
}

const uint32_t* DecodeDeclaration(Shader* psShader, const uint32_t* pui32Token, Declaration* psDecl)
{
    uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
    const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
    const OPCODE_TYPE eOpcode = DecodeOpcodeType(*pui32Token);
    uint32_t ui32OperandOffset = 1;

    psDecl->eOpcode = eOpcode;

    if(bExtended)
    {
        ui32OperandOffset = 2;
    }

    switch (eOpcode)
    {
        case OPCODE_DCL_RESOURCE: // DCL* opcodes have
        {
            psDecl->value.eResourceDimension = DecodeResourceDimension(*pui32Token+ui32OperandOffset);
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_CONSTANT_BUFFER: // custom operand formats.
        {
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_SAMPLER:
        {
            break;
        }
        case OPCODE_DCL_INDEX_RANGE:
        {
            break;
        }
        case OPCODE_DCL_GS_OUTPUT_PRIMITIVE_TOPOLOGY:
        {
            psDecl->value.eOutputPrimitiveTopology = DecodeGSOutputPrimitiveTopology(*pui32Token);
            break;
        }
        case OPCODE_DCL_GS_INPUT_PRIMITIVE:
        {
            psDecl->value.eInputPrimitive = DecodeGSInputPrimitive(*pui32Token);
            break;
        }
        case OPCODE_DCL_MAX_OUTPUT_VERTEX_COUNT:
        {
            psDecl->value.ui32MaxOutputVertexCount = pui32Token[1];
            break;
        }
        case OPCODE_DCL_TESS_PARTITIONING:
        {
            psDecl->value.eTessPartitioning = DecodeTessPartitioning(*pui32Token);
            break;
        }
        case OPCODE_DCL_TESS_DOMAIN:
        {
            psDecl->value.eTessDomain = DecodeTessDomain(*pui32Token);
            break;
        }
        case OPCODE_DCL_TESS_OUTPUT_PRIMITIVE:
        {
            psDecl->value.eTessOutPrim = DecodeTessOutPrim(*pui32Token);
            break;
        }
        case OPCODE_DCL_THREAD_GROUP:
        {
            psDecl->value.aui32WorkGroupSize[0] = pui32Token[1];
            psDecl->value.aui32WorkGroupSize[1] = pui32Token[2];
            psDecl->value.aui32WorkGroupSize[2] = pui32Token[3];
            break;
        }
        case OPCODE_DCL_INPUT:
        {
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_INPUT_SGV:
        {
            break;
        }
        case OPCODE_DCL_INPUT_SIV:
        {
            if(psShader->eShaderType == PIXEL_SHADER)
            {
                psDecl->value.eInterpolation = DecodeInterpolationMode(*pui32Token);
            }
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_INPUT_PS:
        {
            psDecl->ui32NumOperands = 1;
            psDecl->value.eInterpolation = DecodeInterpolationMode(*pui32Token);
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_INPUT_PS_SGV:
        {
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            DecodeNameToken(pui32Token + 3, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_INPUT_PS_SIV:
        {
            psDecl->value.eInterpolation = DecodeInterpolationMode(*pui32Token);
            break;
        }
        case OPCODE_DCL_OUTPUT:
        {
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_OUTPUT_SGV:
        {
            break;
        }
        case OPCODE_DCL_OUTPUT_SIV:
        {
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            DecodeNameToken(pui32Token + 3, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_TEMPS:
        {
            psDecl->value.ui32NumTemps = *(pui32Token+ui32OperandOffset);
            break;
        }
        case OPCODE_DCL_INDEXABLE_TEMP:
        {
            break;
        }
        case OPCODE_DCL_GLOBAL_FLAGS:
        {
            psDecl->value.ui32GlobalFlags = DecodeGlobalFlags(*pui32Token);
            break;
        }
        case OPCODE_DCL_INTERFACE:
        {
            uint32_t funcBody = 0, tableLen, arrayLen, interfaceID;
            interfaceID = pui32Token[ui32OperandOffset];
            ui32OperandOffset++;
            psDecl->ui32TableLength = pui32Token[ui32OperandOffset];
            ui32OperandOffset++;

            tableLen = DecodeInterfaceTableLength(*(pui32Token+ui32OperandOffset));
            arrayLen = DecodeInterfaceArrayLength(*(pui32Token+ui32OperandOffset));

            ui32OperandOffset++;

            psDecl->value.interface.ui32InterfaceID = interfaceID;

            for(;funcBody < tableLen; ++funcBody)
            {
                uint32_t ui32FuncID = *(pui32Token+ui32OperandOffset);
                psShader->functionToInterfaceRemap[ui32FuncID] = interfaceID;
                psDecl->value.interface.aui32Functions[funcBody] = ui32FuncID;
                ui32OperandOffset++;
            }

            break;
        }
        case OPCODE_DCL_FUNCTION_BODY:
        {
            psDecl->ui32NumOperands = 1;
            DecodeOperand(pui32Token+ui32OperandOffset, &psDecl->asOperands[0]);
            break;
        }
        case OPCODE_DCL_FUNCTION_TABLE:
        {
            break;
        }
		case OPCODE_DCL_INPUT_CONTROL_POINT_COUNT:
		{
			break;
		}
		case OPCODE_HS_DECLS:
		{
			break;
		}
		case OPCODE_DCL_OUTPUT_CONTROL_POINT_COUNT:
		{
			//const uint32_t ui32OutputControlPointCount = *(pui32Token+ui32OperandOffset);
			break;
		}
		case OPCODE_HS_FORK_PHASE:
		{
			break;
		}
		case OPCODE_DCL_HS_FORK_PHASE_INSTANCE_COUNT:
		{
            psDecl->value.ui32HullPhaseInstanceCount = pui32Token[1];
			break;
		}
		case OPCODE_CUSTOMDATA:
		{
			ui32TokenLength = pui32Token[1];
			{
				int iTupleSrc = 0, iTupleDest = 0;
				//const uint32_t ui32ConstCount = pui32Token[1] - 2;
				//const uint32_t ui32TupleCount = (ui32ConstCount / 4);
				CUSTOMDATA_CLASS eClass = DecodeCustomDataClass(pui32Token[0]);

				const uint32_t ui32NumVec4 = (ui32TokenLength - 2) / 4;
				uint32_t uIdx = 0;

				ICBVec4 const *pVec4Array = (void*) (pui32Token + 2);

				//The buffer will contain at least one value, but not more than 4096 scalars/1024 vec4's.
				ASSERT(ui32NumVec4 < MAX_IMMEDIATE_CONST_BUFFER_VEC4_SIZE);
		
				/* must be a multiple of 4 */
				ASSERT(((ui32TokenLength - 2) % 4) == 0);

				for (uIdx = 0; uIdx < ui32NumVec4; uIdx++)
				{
					psDecl->asImmediateConstBuffer[uIdx] = pVec4Array[uIdx];
				}

				psDecl->ui32NumOperands = ui32NumVec4;
			}
			break;
		}
        default:
        {
            //Reached end of declarations
            return 0;
        }
    }

    return pui32Token + ui32TokenLength;
}

const uint32_t* DeocdeInstruction(const uint32_t* pui32Token, Instruction* psInst, Shader* psShader)
{
    uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
    const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
    const OPCODE_TYPE eOpcode = DecodeOpcodeType(*pui32Token);
    uint32_t ui32OperandOffset = 1;

#ifdef _DEBUG
    psInst->id = instructionID++;
#endif

    psInst->eOpcode = eOpcode;

    psInst->bSaturate = DecodeInstructionSaturate(*pui32Token);

    if(bExtended)
    {
        do {
			ui32OperandOffset++;
		}
		while(DecodeIsOpcodeExtended(pui32Token[ui32OperandOffset-1]));
    }

    if(eOpcode < NUM_OPCODES && eOpcode >= 0)
    {
        psShader->aiOpcodeUsed[eOpcode] = 1;
    }

    switch (eOpcode)
    {
        //no operands
        case OPCODE_CUT:
        case OPCODE_EMIT:
        case OPCODE_EMITTHENCUT:
        case OPCODE_RET:
        case OPCODE_LOOP:
        case OPCODE_ENDLOOP:
        case OPCODE_BREAK:
        case OPCODE_ELSE:
        case OPCODE_ENDIF:
        case OPCODE_CONTINUE:
        case OPCODE_DEFAULT:
        case OPCODE_ENDSWITCH:
        case OPCODE_NOP:
		case OPCODE_HS_CONTROL_POINT_PHASE:
		case OPCODE_HS_FORK_PHASE:
		case OPCODE_HS_JOIN_PHASE:
        {
            break;
        }
		case OPCODE_DCL_HS_FORK_PHASE_INSTANCE_COUNT:
		{
			break;
		}
        case OPCODE_SYNC:
        {
            psInst->ui32SyncFlags = DecodeSyncFlags(*pui32Token);
            break;
        }

        //1 operand
        case OPCODE_EMIT_STREAM:
        case OPCODE_CUT_STREAM:
        case OPCODE_EMITTHENCUT_STREAM:
        case OPCODE_CASE:
        case OPCODE_SWITCH:
        case OPCODE_LABEL:
        case OPCODE_COUNTBITS:
        case OPCODE_FIRSTBIT_HI:
        case OPCODE_FIRSTBIT_LO:
        case OPCODE_FIRSTBIT_SHI:
        case OPCODE_BFREV:
        {
            psInst->ui32NumOperands = 1;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);

			if(eOpcode == OPCODE_CASE)
			{
				psInst->asOperands[0].iIntegerImmediate = 1;
			}
            break;
        }

        case OPCODE_INTERFACE_CALL:
        {
            psInst->ui32NumOperands = 1;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            psInst->ui32FunctionIDToCall = pui32Token[1];
            break;
        }

	/* Floating point instruction decodes */

        //Instructions with two operands go here
        case OPCODE_MOV:
		case OPCODE_LOG:
		case OPCODE_RSQ:
		case OPCODE_EXP:
		case OPCODE_SQRT:
        case OPCODE_ROUND_PI:
		case OPCODE_ROUND_NI:
		case OPCODE_ROUND_Z:
		case OPCODE_ROUND_NE:
		case OPCODE_FRC:
		case OPCODE_FTOU:
		case OPCODE_FTOI:
        case OPCODE_UTOF:
		case OPCODE_ITOF:
        {
            psInst->ui32NumOperands = 2;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            break;
        }

        //Instructions with three operands go here
        case OPCODE_SINCOS:
		case OPCODE_MIN:
		case OPCODE_IMAX:
		case OPCODE_MAX:
		case OPCODE_MUL:
		case OPCODE_DIV:
		case OPCODE_ADD:
		case OPCODE_DP2:
		case OPCODE_DP3:
		case OPCODE_DP4:
        case OPCODE_NE:
        case OPCODE_OR:
        case OPCODE_LT:
        case OPCODE_IEQ:
        case OPCODE_IADD:
        case OPCODE_AND:
        case OPCODE_GE:
        case OPCODE_IGE:
		case OPCODE_EQ:
		case OPCODE_ISHL:
		case OPCODE_LD:
		case OPCODE_IMUL:
		case OPCODE_UDIV:
		case OPCODE_ILT:
        {
            psInst->ui32NumOperands = 3;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[2]);
            break;
        }
        //Instructions with four operands go here
		case OPCODE_MAD:
        case OPCODE_MOVC:
		case OPCODE_IMAD:
		{
            psInst->ui32NumOperands = 4;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[2]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[3]);
            break;
		}
        case OPCODE_SAMPLE:
        case OPCODE_GATHER4:
        {
            psInst->ui32NumOperands = 4;

            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[2]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[3]);
            break;
        }
        case OPCODE_SAMPLE_L:
        case OPCODE_BFI:
        {
            psInst->ui32NumOperands = 5;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[2]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[3]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[4]);
            break;
        }
        case OPCODE_IF:
        case OPCODE_BREAKC:
        case OPCODE_CALLC:
        case OPCODE_CONTINUEC:
        case OPCODE_RETC:
        case OPCODE_DISCARD:
        {
            psInst->eBooleanTestType = DecodeInstrTestBool(*pui32Token);
            psInst->ui32NumOperands = 2;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            break;
        }
		case OPCODE_CUSTOMDATA:
		{
			ui32TokenLength = pui32Token[1];
			break;
		}
        default:
        {
			ASSERT(0);
            break;
        }
    }

    return pui32Token + ui32TokenLength;
}

void Decode(const uint32_t* pui32Tokens, const uint32_t* pui32Resources, Shader* psShader)
{
	const uint32_t* pui32CurrentToken = pui32Tokens;
    const uint32_t ui32ShaderLength = pui32Tokens[1];
    Instruction* psInst;
    Declaration* psDecl;
	psShader->ui32MajorVersion = DecodeProgramMajorVersion(*pui32CurrentToken);
	psShader->ui32MinorVersion = DecodeProgramMinorVersion(*pui32CurrentToken);
	psShader->eShaderType = DecodeShaderType(*pui32CurrentToken);

	pui32CurrentToken++;//Move to shader length
	psShader->ui32ShaderLength = ui32ShaderLength;
    pui32CurrentToken++;//Move to after shader length (usually a declaration)

    //Using ui32ShaderLength as the instruction count
    //will allocate more than enough memory. Avoids having to
    //traverse the entire shader just to get the real instruction count.
    psInst = malloc(sizeof(Instruction) * ui32ShaderLength);
    psShader->psInst = psInst;
    psShader->ui32InstCount = 0;

    psDecl = malloc(sizeof(Declaration) * ui32ShaderLength);
    psShader->psDecl = psDecl;
    psShader->ui32DeclCount = 0;

    ReadResources(pui32Resources, &psShader->sInfo);

    while(1) //Keep going until we reach the first non-declaration token, or the end of the shader.
    {
        const uint32_t* pui32Result = DecodeDeclaration(psShader, pui32CurrentToken, psDecl);
        
        if(pui32Result)
        {
            pui32CurrentToken = pui32Result;
            psShader->ui32DeclCount++;
            psDecl++;

            if(pui32CurrentToken >= (pui32Tokens + ui32ShaderLength))
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    while (pui32CurrentToken < (pui32Tokens + ui32ShaderLength))
    {
        const uint32_t* nextInstr = DeocdeInstruction(pui32CurrentToken, psInst, psShader);

#ifdef _DEBUG
        if(nextInstr == pui32CurrentToken)
        {
            ASSERT(0);
            break;
        }
#endif

        pui32CurrentToken = nextInstr;
        psShader->ui32InstCount++;
        psInst++;
    }
}

Shader* DecodeDXBC(uint32_t* data)
{
    Shader* psShader;
	DXBCContainerHeader* header = (DXBCContainerHeader*)data;
	uint32_t i;
	uint32_t chunkCount;
	uint32_t* chunkOffsets;
    DXBCChunkHeader* rdefChunk = 0;

	if(header->fourcc != FOURCC_DXBC)
	{
		return 0;
	}

	chunkOffsets = (uint32_t*)(header + 1);

	chunkCount = header->chunkCount;

	for(i = 0; i < chunkCount; ++i)
	{
		uint32_t offset = chunkOffsets[i];

		DXBCChunkHeader* chunk = (DXBCChunkHeader*)((char*)data + offset);

        if(chunk->fourcc == FOURCC_RDEF)
        {
            rdefChunk = chunk;
        }

		if(chunk->fourcc == FOURCC_SHDR ||
			chunk->fourcc == FOURCC_SHEX)
		{
            psShader = calloc(1, sizeof(Shader));
			Decode((uint32_t*)(chunk + 1), (uint32_t*)(rdefChunk + 1), psShader);
			return psShader;
		}
	}
    return 0;
}

