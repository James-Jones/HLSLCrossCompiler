
#include "internal_includes/tokens.h"
#include "internal_includes/structs.h"
#include "internal_includes/decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "internal_includes/reflect.h"
#include "internal_includes/debug.h"

#define FOURCC(a, b, c, d) ((uint32_t)(uint8_t)(a) | ((uint32_t)(uint8_t)(b) << 8) | ((uint32_t)(uint8_t)(c) << 16) | ((uint32_t)(uint8_t)(d) << 24 ))
static enum {FOURCC_CTAB = FOURCC('C', 'T', 'A', 'B')}; //Constant table

#ifdef _DEBUG
static uint64_t operandID = 0;
static uint64_t instructionID = 0;
#endif

static uint32_t aui32ImmediateConst[256];

static void DecodeOperandDX9(const uint32_t ui32Token,
							 const uint32_t ui32Token1,
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
        case OPERAND_TYPE_DX9_CONST:
        {
            if(aui32ImmediateConst[ui32RegNum])
            {
                psOperand->eType = OPERAND_TYPE_SPECIAL_IMMCONST;
            }
            else
            {
                psOperand->eType = OPERAND_TYPE_CONSTANT_BUFFER;
            }
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
    else
    if(psDecl->asOperands[0].eType == OPERAND_TYPE_CONSTANT_BUFFER)
    {
        psDecl->eOpcode = OPCODE_DCL_CONSTANT_BUFFER;

        ASSERT(psShader->sInfo.ui32NumConstantBuffers);

        psDecl->asOperands[0].aui32ArraySizes[0] = 0;//Const buffer index
        psDecl->asOperands[0].aui32ArraySizes[1] = psShader->sInfo.psConstantBuffers[0].ui32TotalSizeInBytes / 16;//Number of vec4 constants.
    }
}

static void DefineDX9(Shader* psShader,
                      const uint32_t ui32RegNum,
                      const uint32_t c0,
                      const uint32_t c1,
                      const uint32_t c2,
                      const uint32_t c3,
                      Declaration* psDecl)
{
    psDecl->eOpcode = OPCODE_SPECIAL_DCL_IMMCONST;
    psDecl->ui32NumOperands = 2;

    memset(&psDecl->asOperands[0], 0, sizeof(Operand));
    psDecl->asOperands[0].eType = OPERAND_TYPE_SPECIAL_IMMCONST;
    psDecl->asOperands[0].ui32RegisterNumber = ui32RegNum;

    aui32ImmediateConst[ui32RegNum] = 1;

    memset(&psDecl->asOperands[1], 0, sizeof(Operand));
    psDecl->asOperands[1].eType = OPERAND_TYPE_IMMEDIATE32;
    psDecl->asOperands[1].iNumComponents = 4;
    psDecl->asOperands[1].afImmediates[0] = *((float*)&c0);
    psDecl->asOperands[1].afImmediates[1] = *((float*)&c1);
    psDecl->asOperands[1].afImmediates[2] = *((float*)&c2);
    psDecl->asOperands[1].afImmediates[3] = *((float*)&c3);
}

static void CreateD3D10Instruction(Instruction* psInst,
    const OPCODE_TYPE eType,
    const uint32_t bHasDest,
    const uint32_t ui32SrcCount,
    const uint32_t* pui32Tokens)
{
    uint32_t ui32Src;
    uint32_t ui32Offset = 1;

    memset(psInst, 0, sizeof(Instruction));

#ifdef _DEBUG
    psInst->id = instructionID++;
#endif

    psInst->eOpcode = eType;

    if(bHasDest)
    {
        DecodeOperandDX9(pui32Tokens[ui32Offset],
            pui32Tokens[ui32Offset+1],
            &psInst->asOperands[0]);

        ui32Offset++;
    }

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
    uint32_t bDeclareConstantTable = 0;
    Shader* psShader = calloc(1, sizeof(Shader));

    memset(aui32ImmediateConst, 0, 256);

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
            if(pui32CurrentToken[1] == FOURCC_CTAB)
            {
                ++ui32NumDeclarations;
                bDeclareConstantTable = 1;
            }
        }
        else if(eOpcode == OPCODE_DX9_DCL || eOpcode == OPCODE_DX9_DEF)
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

            if(pui32CurrentToken[1] == FOURCC_CTAB)
            {
                LoadD3D9ConstantTable((char*)(&pui32CurrentToken[2]), &psShader->sInfo);
            }
        }
        else if(eOpcode == OPCODE_DX9_DCL)
        {
            DecodeDeclarationDX9(psShader, pui32CurrentToken[0], pui32CurrentToken[1], &psDecl[decl]);
            decl++;
        }
        else if(eOpcode == OPCODE_DX9_DEF)
        {
            const uint32_t ui32Const0 = *(pui32CurrentToken+2);
            const uint32_t ui32Const1 = *(pui32CurrentToken+3);
            const uint32_t ui32Const2 = *(pui32CurrentToken+4);
            const uint32_t ui32Const3 = *(pui32CurrentToken+5);

            DefineDX9(psShader,
                DecodeOperandRegisterNumberDX9(pui32CurrentToken[1]),
                ui32Const0,
                ui32Const1,
                ui32Const2,
                ui32Const3,
                &psDecl[decl]);
            decl++;
        }
        else
        {
            switch(eOpcode)
            {
                case OPCODE_DX9_MOV:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MOV, 1, 1, pui32CurrentToken);
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
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ADD, 1, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_SUB:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ADD, 1, 2, pui32CurrentToken);
                    ASSERT(psInst[inst].asOperands[2].eModifier == OPERAND_MODIFIER_NONE);
                    psInst[inst].asOperands[2].eModifier = OPERAND_MODIFIER_NEG;
                    break;
                }
                case OPCODE_DX9_MAD:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MAD, 1, 3, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_MUL:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MUL, 1, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_RCP:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_RCP, 1, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_RSQ:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_RSQ, 1, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_DP3:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_DP3, 1, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_DP4:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_DP4, 1, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_MIN:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MIN, 1, 2, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_MAX:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_MAX, 1, 2, pui32CurrentToken);
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
                    CreateD3D10Instruction(&psInst[inst], OPCODE_EXP, 1, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_LOG:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_LOG, 1, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_NRM:
                {
                    //Convert NRM RESULT, SRCA into:
                    //dp4 RESULT, SRCA, SRCA
                    //rsq RESULT, RESULT

                    CreateD3D10Instruction(&psInst[inst], OPCODE_DP4, 1, 1, pui32CurrentToken);
                    memcpy(&psInst[inst].asOperands[2],&psInst[inst].asOperands[1], sizeof(Operand));
                    ++inst;

                    CreateD3D10Instruction(&psInst[inst], OPCODE_RSQ, 0, 0, pui32CurrentToken);
                    memcpy(&psInst[inst].asOperands[0],&psInst[inst-1].asOperands[0], sizeof(Operand));
                    break;
                }
                case OPCODE_DX9_SINCOS:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_SINCOS, 1, 3, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_FRC:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_FRC, 1, 1, pui32CurrentToken);
                    break;
                }

                case OPCODE_DX9_MOVA:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ROUND_NE, 1, 1, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_DST:
                case OPCODE_DX9_LRP:
                
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
                
                case OPCODE_DX9_REP:
                case OPCODE_DX9_ENDREP:
                case OPCODE_DX9_IF:
                case OPCODE_DX9_IFC:
                case OPCODE_DX9_ELSE:
                case OPCODE_DX9_BREAKC:
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
                    CreateD3D10Instruction(&psInst[inst], OPCODE_NOP, 0, 0, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_LOOP:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_LOOP, 0, 0, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_RET:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_RET, 0, 0, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_ENDLOOP:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ENDLOOP, 0, 0, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_ENDIF:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_ENDIF, 0, 0, pui32CurrentToken);
                    break;
                }
                case OPCODE_DX9_BREAK:
                {
                    CreateD3D10Instruction(&psInst[inst], OPCODE_BREAK, 0, 0, pui32CurrentToken);
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
        if(bDeclareConstantTable)
        {
            DecodeDeclarationDX9(psShader, 0, CreateOperandTokenDX9(0, OPERAND_TYPE_DX9_RASTOUT), &psDecl[decl+1]);
        }
        else
        {
            DecodeDeclarationDX9(psShader, 0, CreateOperandTokenDX9(0, OPERAND_TYPE_DX9_RASTOUT), &psDecl[decl]);
        }
    }

    if(bDeclareConstantTable)
    {
        DecodeDeclarationDX9(psShader, 0, CreateOperandTokenDX9(0, OPERAND_TYPE_DX9_CONST), &psDecl[decl]);
    }

    return psShader;
}
