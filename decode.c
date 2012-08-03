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
    OPERAND_NUM_COMPONENTS eNumComponents;

    //Some defaults
    psOperand->iWriteMaskEnabled = 1;
    psOperand->iGSInput = 0;

    psOperand->iExtended = DecodeIsOpcodeExtended(*pui32Tokens);


	/* Check if this instruction is extended.  If it is,
	 * we need to print the information first */
	if (psOperand->iExtended)
	{
		/* OperandToken1 is the second token */
		ui32NumTokens++;
	}

	psOperand->iIndexDims = DecodeOperandIndexDimension(*pui32Tokens);
    psOperand->eType = DecodeOperandType(*pui32Tokens);
    
    if(psOperand->eType == OPERAND_TYPE_SAMPLER ||
       psOperand->eType == OPERAND_TYPE_RESOURCE)
    {
        psOperand->iWriteMaskEnabled = 0;
    }

    psOperand->ui32RegisterNumber = 0xFFFFFFFF;

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

    if(psOperand->eType == OPERAND_TYPE_IMMEDIATE32)
    {
        for(i=0; i< psOperand->iNumComponents; ++i)
        {
            psOperand->afImmediates[i] = *((float*)(&pui32Tokens[1+i]));
            ui32NumTokens ++;
        }
    }


    for(i=0; i <psOperand->iIndexDims; ++i)
    {
        OPERAND_INDEX_REPRESENTATION eRep = DecodeOperandIndexRepresentation(i ,*pui32Tokens);

        psOperand->ui32RegisterNumber = *(pui32Tokens+ui32NumTokens);

        ui32NumTokens++;
    }

    psOperand->pszSpecialName[0] ='\0';

    //psOperand->ui32RegisterNumber = pui32Tokens[0] & 0x3FF;

    return ui32NumTokens;
}

const uint32_t* DecodeDeclaration(const uint32_t* pui32Token, Declaration* psDecl)
{
    const uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
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
#if 0
		case OPCODE_DCL_GLOBAL_FLAGS:
		{
			printf("dcl_globalFlags\n");
			break;
		}
		case OPCODE_DCL_INPUT:
		{
			printf("dcl_input.\n");
            psDecl->asOperands[0].ui32RegisterNumber = 0;
			break;
		}
		case OPCODE_DCL_OUTPUT_SIV:
		{
            psDecl->ui32NumOperands = 2;
            DecodeOperand(pui32Token+1, &psDecl->asOperands[0]);
            DecodeNameToken(pui32Token + 3, &psDecl->asOperands[0]);
			break;
		}
#endif
        case OPCODE_DCL_RESOURCE: // DCL* opcodes have
        {
            psDecl->eResourceDimension = DecodeResourceDimension(*pui32Token+ui32OperandOffset);
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
            break;
        }
        case OPCODE_DCL_GS_INPUT_PRIMITIVE:
        {
            break;
        }
        case OPCODE_DCL_MAX_OUTPUT_VERTEX_COUNT:
        {
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
            break;
        }
        case OPCODE_DCL_INPUT_PS:
        {
            break;
        }
        case OPCODE_DCL_INPUT_PS_SGV:
        {
            break;
        }
        case OPCODE_DCL_INPUT_PS_SIV:
        {
            break;
        }
        case OPCODE_DCL_OUTPUT:
        {
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
            psDecl->ui32NumTemps = *(pui32Token+ui32OperandOffset);
            break;
        }
        case OPCODE_DCL_INDEXABLE_TEMP:
        {
            break;
        }
        case OPCODE_DCL_GLOBAL_FLAGS:
        {
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

const uint32_t* DeocdeInstruction(const uint32_t* pui32Token, Instruction* psInst)
{
    const uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
    const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
    const OPCODE_TYPE eOpcode = DecodeOpcodeType(*pui32Token);
    uint32_t ui32OperandOffset = 1;

    psInst->eOpcode = eOpcode;

    if(bExtended)
    {
        ui32OperandOffset = 2;
    }

    switch (eOpcode)
    {
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
            psInst->ui32NumOperands = 2;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
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
        case OPCODE_NE:
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
        case OPCODE_SAMPLE:
        {
            psInst->ui32NumOperands = 4;
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[0]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[1]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[2]);
            ui32OperandOffset += DecodeOperand(pui32Token+ui32OperandOffset, &psInst->asOperands[3]);
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
    Declaration* psDecl;
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

    psDecl = malloc(sizeof(Declaration) * ui32ShaderLength);
    psShader->psDecl = psDecl;
    psShader->ui32DeclCount = 0;

    while(1) //Keep going until we reach the first non-declaration token, or the end of the shader.
    {
        const uint32_t* pui32Result = DecodeDeclaration(pui32CurrentToken, psDecl);
        
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

