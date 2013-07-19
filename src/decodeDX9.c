
#include "internal_includes/tokens.h"
#include "internal_includes/structs.h"
#include "internal_includes/decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "internal_includes/reflect.h"
#include "internal_includes/debug.h"

#ifdef _DEBUG
static uint64_t operandID = 0;
static uint64_t instructionID = 0;
#endif

static void DecodeOperandDX9(uint32_t ui32Token,
							 uint32_t ui32Token1,
							 Operand *psOperand)
{
    uint32_t ui32RegNum = DecodeOperandRegisterNumberDX9(ui32Token);
    uint32_t ui32RegType = DecodeOperandTypeDX9(ui32Token);

    switch(ui32RegType)
    {
        case OPERAND_TYPE_DX9_TEMP:
        {
            psOperand->eType = OPERAND_TYPE_TEMP;
            break;
        }
        case OPERAND_TYPE_DX9_INPUT:
        {
            psOperand->eType = OPERAND_TYPE_INPUT;
            break;
        }
        case OPERAND_TYPE_DX9_RASTOUT:
        case OPERAND_TYPE_DX9_ATTROUT:
        {
            psOperand->eType = OPERAND_TYPE_OUTPUT;
            break;
        }
    }

    psOperand->ui32RegisterNumber = ui32RegNum;

#ifdef _DEBUG
    psOperand->id = operandID++;
#endif

    psOperand->iWriteMaskEnabled = 0;
    psOperand->iGSInput = 0;
    psOperand->iExtended = 0;
    psOperand->eModifier = OPERAND_MODIFIER_NONE;
    psOperand->psSubOperand[0] = 0;
    psOperand->psSubOperand[1] = 0;
    psOperand->psSubOperand[2] = 0;

    psOperand->iIndexDims = INDEX_0D;
    psOperand->iNumComponents = 4;
    psOperand->iIntegerImmediate = 0;

    psOperand->pszSpecialName[0] ='\0';
}

static void DecodeDeclarationDX9(Shader* psShader,
                                const uint32_t ui32Token0,
                                const uint32_t ui32Token1,
                                Declaration* psDecl)
{
    uint32_t ui32Usage = DecodeUsageDX9(ui32Token0);
    uint32_t ui32UsageIndex = DecodeUsageIndexDX9(ui32Token0);
    uint32_t ui32RegNum = DecodeOperandRegisterNumberDX9(ui32Token1);
    uint32_t ui32RegType = DecodeOperandTypeDX9(ui32Token1);

    psDecl->eOpcode = OPCODE_DCL_INPUT;
    psDecl->ui32NumOperands = 1;
    DecodeOperandDX9(ui32Token1, 0, &psDecl->asOperands[0]);

    if(psDecl->asOperands[0].eType == OPERAND_TYPE_OUTPUT)
    {
        psDecl->eOpcode = OPCODE_DCL_OUTPUT;
        if(psDecl->asOperands[0].ui32RegisterNumber==0)
        {
            psDecl->eOpcode = OPCODE_DCL_OUTPUT_SIV;
            //gl_Position
            psDecl->asOperands[0].eSpecialName = NAME_POSITION;
        }
    }
}


void CreateD3D10Instruction(Instruction* psInst, const OPCODE_TYPE eType, uint32_t ui32SrcCount, const uint32_t* pui32Tokens)
{
    uint32_t ui32Src;
    uint32_t ui32Offset = 1;

    memset(psInst, 0, sizeof(Instruction));

    psInst->eOpcode = eType;

    DecodeOperandDX9(pui32Tokens[ui32Offset],
        pui32Tokens[ui32Offset+1],
        &psInst->asOperands[0]);

    ui32Offset++;

    for(ui32Src=0; ui32Src < ui32SrcCount; ++ui32Src)
    {
        DecodeOperandDX9(pui32Tokens[ui32Offset],
            pui32Tokens[ui32Offset+1],
            &psInst->asOperands[1+ui32Src]);

        ui32Offset++;
    }
}

Shader* DecodeDX9BC(const uint32_t* pui32Tokens)
{
    const uint32_t* pui32CurrentToken = pui32Tokens;
    uint32_t ui32NumInstructions = 0;
    uint32_t ui32NumDeclarations = 0;
    Instruction* psInst;
    Declaration* psDecl;
    uint32_t decl, inst;
    Shader* psShader = calloc(1, sizeof(Shader));;

	psShader->ui32MajorVersion = DecodeProgramMajorVersionDX9(*pui32CurrentToken);
	psShader->ui32MinorVersion = DecodeProgramMinorVersionDX9(*pui32CurrentToken);
	psShader->eShaderType = DecodeShaderTypeDX9(*pui32CurrentToken);

    pui32CurrentToken++;

    //Work out how many instructions and declarations we need to allocate memory for.
	while (1)
	{
		OPCODE_TYPE_DX9 eOpcode = DecodeOpcodeTypeDX9(pui32CurrentToken[0]);
		uint32_t ui32InstLen = DecodeInstructionLengthDX9(pui32CurrentToken[0]);

        if(eOpcode == OPCODE_DX9_END)
        {
            break;
        }
        else if(eOpcode == OPCODE_DX9_COMMENT)
        {
            ui32InstLen = DecodeCommentLengthDX9(pui32CurrentToken[0]);
        }
        else if(eOpcode == OPCODE_DX9_DCL)
        {
            ++ui32NumDeclarations;
        }
        else
        {
            switch(eOpcode)
            {
                case OPCODE_DX9_NRM:
                {
                    //Emulate with dp4 and rsq
                    ui32NumInstructions += 2;
                    break;
                }
                default:
                {
                    ++ui32NumInstructions;
                    break;
                }
            }
        }

        pui32CurrentToken += ui32InstLen + 1;
    }

    psInst = malloc(sizeof(Instruction) * ui32NumInstructions);
    psShader->psInst = psInst;
    psShader->ui32InstCount = ui32NumInstructions;

    if(psShader->eShaderType == VERTEX_SHADER)
    {
        //Declare gl_Position. vs_3_0 does declare it, SM1/2 do not
        ui32NumDeclarations++;
    }

    psDecl = malloc(sizeof(Declaration) * ui32NumDeclarations);
    psShader->psDecl = psDecl;
    psShader->ui32DeclCount = ui32NumDeclarations;

    pui32CurrentToken = pui32Tokens + 1;

    inst=0;
    decl=0;
    while (1)
    {
		OPCODE_TYPE_DX9 eOpcode = DecodeOpcodeTypeDX9(pui32CurrentToken[0]);
		uint32_t ui32InstLen = DecodeInstructionLengthDX9(pui32CurrentToken[0]);

        if(eOpcode == OPCODE_DX9_END)
        {
            break;
        }
        else if(eOpcode == OPCODE_DX9_COMMENT)
        {
            ui32InstLen = DecodeCommentLengthDX9(pui32CurrentToken[0]);
        }
        else if(eOpcode == OPCODE_DX9_DCL)
        {
            DecodeDeclarationDX9(psShader, pui32CurrentToken[0], pui32CurrentToken[1], &psDecl[decl]);
            decl++;
        }
        else
        {
            switch(eOpcode)
            {
                case OPCODE_DX9_MOV:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MOV, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_LIT:
                {
                    /*Dest.x = 1
                      Dest.y = (Src0.x > 0) ? Src0.x : 0
                      Dest.z = (Src0.x > 0 && Src0.y > 0) ? pow(Src0.y, Src0.w) : 0
                      Dest.w = 1
                    */
                    ASSERT(0);
                    break;
                }
                case OPCODE_DX9_ADD:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ADD, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_SUB:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ADD, 2, pui32CurrentToken);
                    ASSERT(psInst[inst].asOperands[2].eModifier == OPERAND_MODIFIER_NONE);
                    psInst[inst].asOperands[2].eModifier = OPERAND_MODIFIER_NEG;
                    break;
                }
                case OPCODE_DX9_MAD:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MAD, 3, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_MUL:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MUL, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_RCP:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_RCP, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_RSQ:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_RSQ, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_DP3:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_DP3, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_DP4:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_DP4, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_MIN:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MIN, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_MAX:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MAX, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_SLT:
                case OPCODE_DX9_SGE:
                {
                    ASSERT(0);
                    break;
                }
                case OPCODE_DX9_EXP:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_EXP, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_LOG:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_LOG, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_NRM:
                {
                    //Convert NRM RESULT, SRCA into:
                    //dp4 RESULT, SRCA, SRCA
                    //rsq RESULT, RESULT

                    CreateD3D10Instruction(&psInst[inst], OPCODE_DP4, 1, pui32CurrentToken);
                    memcpy(&psInst[inst].asOperands[2],&psInst[inst].asOperands[1], sizeof(Operand));
                    ++inst;
                    psInst[inst].eOpcode = OPCODE_RSQ;
                    memcpy(&psInst[inst].asOperands[0],&psInst[inst-1].asOperands[0], sizeof(Operand));
                    break;
                }
                case OPCODE_DX9_DST:
                case OPCODE_DX9_LRP:
                case OPCODE_DX9_FRC:
                case OPCODE_DX9_M4x4:
                case OPCODE_DX9_M4x3:
                case OPCODE_DX9_M3x4:
                case OPCODE_DX9_M3x3:
                case OPCODE_DX9_M3x2:
                case OPCODE_DX9_CALL:
                case OPCODE_DX9_CALLNZ:
                case OPCODE_DX9_LABEL:
                case OPCODE_DX9_POW:
                case OPCODE_DX9_CRS:
                case OPCODE_DX9_SGN:
                case OPCODE_DX9_ABS:
                case OPCODE_DX9_SINCOS:
                case OPCODE_DX9_REP:
                case OPCODE_DX9_ENDREP:
                case OPCODE_DX9_IF:
                case OPCODE_DX9_IFC:
                case OPCODE_DX9_ELSE:
                case OPCODE_DX9_BREAKC:
                case OPCODE_DX9_MOVA:
                case OPCODE_DX9_DEFB:
                case OPCODE_DX9_DEFI:

                case OPCODE_DX9_TEXCOORD:
                case OPCODE_DX9_TEXKILL:
                case OPCODE_DX9_TEX:
                case OPCODE_DX9_TEXBEM:
                case OPCODE_DX9_TEXBEML:
                case OPCODE_DX9_TEXREG2AR:
                case OPCODE_DX9_TEXREG2GB:
                case OPCODE_DX9_TEXM3x2PAD:
                case OPCODE_DX9_TEXM3x2TEX:
                case OPCODE_DX9_TEXM3x3PAD:
                case OPCODE_DX9_TEXM3x3TEX:
                case OPCODE_DX9_TEXM3x3SPEC:
                case OPCODE_DX9_TEXM3x3VSPEC:
                case OPCODE_DX9_EXPP:
                case OPCODE_DX9_LOGP:
                case OPCODE_DX9_CND:
                case OPCODE_DX9_DEF:
                case OPCODE_DX9_TEXREG2RGB:
                case OPCODE_DX9_TEXDP3TEX:
                case OPCODE_DX9_TEXM3x2DEPTH:
                case OPCODE_DX9_TEXDP3:
                case OPCODE_DX9_TEXM3x3:
                case OPCODE_DX9_TEXDEPTH:
                case OPCODE_DX9_CMP:
                case OPCODE_DX9_BEM:
                case OPCODE_DX9_DP2ADD:
                case OPCODE_DX9_DSX:
                case OPCODE_DX9_DSY:
                case OPCODE_DX9_TEXLDD:
                case OPCODE_DX9_SETP:
                case OPCODE_DX9_TEXLDL:
                case OPCODE_DX9_BREAKP:
                {
                    ASSERT(0);
                    break;
                }
                case OPCODE_DX9_NOP:
                case OPCODE_DX9_PHASE:
                {
                    psInst[inst].eOpcode = OPCODE_NOP;
                    break;
                }
                case OPCODE_DX9_LOOP:
                {
                    psInst[inst].eOpcode = OPCODE_LOOP;
                    break;
                }
                case OPCODE_DX9_RET:
                {
                    psInst[inst].eOpcode = OPCODE_RET;
                    break;
                }
                case OPCODE_DX9_ENDLOOP:
                {
                    psInst[inst].eOpcode = OPCODE_ENDLOOP;
                    break;
                }
                case OPCODE_DX9_ENDIF:
                {
                    psInst[inst].eOpcode = OPCODE_ENDIF;
                    break;
                }
                case OPCODE_DX9_BREAK:
                {
                    psInst[inst].eOpcode = OPCODE_BREAK;
                    break;
                }
                default:
                {
                    ASSERT(0);
                    break;
                }
            }
            inst++;
        }

        pui32CurrentToken += ui32InstLen + 1;
    }

    if(psShader->eShaderType == VERTEX_SHADER)
    {
        //Declare gl_Position. vs_3_0 does declare it, SM1/2 do not
        DecodeDeclarationDX9(psShader, 0, CreateOperandTokenDX9(0, OPERAND_TYPE_DX9_RASTOUT), &psDecl[decl]);
    }

    return psShader;
}
