#include "tokens.h"
#include "structs.h"
#include "printdecode.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"

#define FOURCC(a, b, c, d) ((uint32_t)(uint8_t)(a) | ((uint32_t)(uint8_t)(b) << 8) | ((uint32_t)(uint8_t)(c) << 16) | ((uint32_t)(uint8_t)(d) << 24 ))
const uint32_t FOURCC_DXBC = FOURCC('D', 'X', 'B', 'C');
const uint32_t FOURCC_SHDR = FOURCC('S', 'H', 'D', 'R');
const uint32_t FOURCC_SHEX = FOURCC('S', 'H', 'E', 'X');

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
        default:
        {
            printf("Unknown name token\n");
            break;
        }
    }

    return;
}

uint32_t DecodeOperand (const uint32_t *pui32Tokens, Operand* psOperand)
{
    int i;
	uint32_t ui32NumTokens = 1;

    //Some defaults
    psOperand->iWriteMaskEnabled = 1;
    psOperand->iGSInput = 0;

    psOperand->iExtended = DecodeIsOpcodeExtended(*pui32Tokens);

	/* Check if this instruction is extended.  If it is,
	 * we need to print the information first */
	if (psOperand->iExtended)
	{
		/* OperandToken1 is the second token */

        printf("Extended\n");

		ui32NumTokens++;
        //TODO
	}

	psOperand->iIndexDims = DecodeOperandIndexDimension(*pui32Tokens);
    psOperand->eType = DecodeOperandType(*pui32Tokens);

    psOperand->ui32RegisterNumber = 0xFFFFFFFF;

    printf("dims = %d\n", psOperand->iIndexDims);

    if(psOperand->eType == OPERAND_TYPE_IMMEDIATE32)
    {
        printf("Immediate. %f %f %f %f\n", *((float*)(&pui32Tokens[1])),
            *((float*)(&pui32Tokens[2])),
            *((float*)(&pui32Tokens[3])),
            *((float*)(&pui32Tokens[4])));
    }

    for(i=0; i <psOperand->iIndexDims; ++i)
    {
        OPERAND_INDEX_REPRESENTATION eRep = DecodeOperandIndexRepresentation(i ,*pui32Tokens);
        printf("rep = %d\n", eRep);

        psOperand->ui32RegisterNumber = *(pui32Tokens+ui32NumTokens);

        ui32NumTokens++;
    }

    //psOperand->ui32RegisterNumber = pui32Tokens[0] & 0x3FF;

    return ui32NumTokens;
}

const uint32_t* DeocdeInstruction(const uint32_t* pui32Token, Instruction* psInst)
{
    const uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
    const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
    const OPCODE_TYPE eOpcode = DecodeOpcodeType(*pui32Token);

    psInst->eOpcode = eOpcode;

    switch (eOpcode)
    {
		case OPCODE_DCL_GLOBAL_FLAGS:
		{
			printf("dcl_globalFlags\n");
			break;
		}
		case OPCODE_DCL_INPUT:
		{
			printf("dcl_input.\n");
            psInst->asOperands[0].ui32RegisterNumber = 0;
			break;
		}
		case OPCODE_DCL_OUTPUT_SIV:
		{
            psInst->ui32NumOperands = 2;
            DecodeOperand(pui32Token+1, &psInst->asOperands[0]);
            DecodeNameToken(pui32Token + 3, &psInst->asOperands[0]);
			break;
		}

		case OPCODE_RET:
		{
			printf("RET.\n");
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
        {
            uint32_t ui32Length = 0;
            psInst->ui32NumOperands = 2;
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[0]);
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[1]);
            break;
        }

        //Instructions with three operands go here
        case OPCODE_SINCOS:
		case OPCODE_MIN:
		case OPCODE_MAX:
		case OPCODE_MUL:
		case OPCODE_DIV:
		case OPCODE_ADD:
		case OPCODE_DP2:
		case OPCODE_DP3:
		case OPCODE_DP4:
        {
            uint32_t ui32Length = 0;
            psInst->ui32NumOperands = 3;
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[0]);
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[1]);
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[2]);
            break;
        }
        //Instructions with four operands go here
		case OPCODE_MAD:
        {
            uint32_t ui32Length = 0;
            psInst->ui32NumOperands = 4;
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[0]);
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[1]);
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[2]);
            ui32Length += DecodeOperand(pui32Token+ui32Length, &psInst->asOperands[3]);
            break;
        }
        default:
        {
			printf("Unkown opcode.\n");
            break;
        }
    }

    return pui32Token + ui32TokenLength;
}

void Decode(const uint32_t* pui32Tokens, Shader* psShader)
{
	const uint32_t* pui32CurrentToken = pui32Tokens;
    const uint32_t ui32ShaderLength = pui32Tokens[1];
    Instruction* psInst;
	psShader->ui32MajorVersion = DecodeProgramMajorVersion(*pui32CurrentToken);
	psShader->ui32MinorVersion = DecodeProgramMinorVersion(*pui32CurrentToken);
	psShader->eShaderType = DecodeShaderType(*pui32CurrentToken);
	pui32CurrentToken++;
	psShader->ui32ShaderLength = ui32ShaderLength;

    pui32CurrentToken++;//Shader length
	pui32CurrentToken++;//After shader length (usually a declaration)

    //Using ui32ShaderLength as the instruction count
    //will allocate more than enough memory. Avoids having to
    //traverse the entire shader just to get the real instruction count.
    psInst = malloc(sizeof(Instruction) * ui32ShaderLength);
    psShader->psInst = psInst;

    psShader->ui32InstCount = 0;

    while (pui32CurrentToken < (pui32Tokens + ui32ShaderLength))
    {
        pui32CurrentToken = DeocdeInstruction(pui32CurrentToken, psInst);
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

	if(header->fourcc != FOURCC_DXBC)
	{
		printf("Bad fourcc\n");
		return 0;
	}

	chunkOffsets = (uint32_t*)(header + 1);

	chunkCount = header->chunkCount;

	for(i = 0; i < chunkCount; ++i)
	{
		uint32_t offset = chunkOffsets[i];

		DXBCChunkHeader* chunk = (DXBCChunkHeader*)((char*)data + offset);

		if(chunk->fourcc == FOURCC_SHDR ||
			chunk->fourcc == FOURCC_SHEX)
		{
            psShader = malloc(sizeof(Shader));
			Decode((uint32_t*)(chunk + 1), psShader);
			printf("Success!\n");
			return psShader;
		}
	}

	printf("Failed - No SHEX ro SHDR fourcc found.\n");
    return 0;
}

