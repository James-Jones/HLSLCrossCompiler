#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Register_TAG
{
    const char* specialName;
    int type;
    int number;
} Register;

typedef struct Operand_TAG
{
    int iExtended;
    OPERAND_TYPE eType;
    int modifier;
    int iIndexDims;
    int indexRepresentation[4];
    int writeMask;
    int iGSInput;
    int iWriteMaskEnabled;

    uint32_t ui32RegisterNumber;


    SPECIAL_NAME eSpecialName;
    char pszSpecialName[64];
} Operand;

typedef struct Instruction_TAG
{
    OPCODE_TYPE eOpcode;
    uint32_t ui32NumOperands;
    Operand asOperands[4];
} Instruction;

typedef struct Declaration_TAG
{
    int type;
} Declaration;

typedef struct Shader_TAG
{
    uint32_t ui32MajorVersion;
    uint32_t ui32MinorVersion;
    SHADER_TYPE eShaderType;

    //DWORDs in program code, including version and length tokens.
    uint32_t ui32ShaderLength;

    uint32_t numDecl;
    Declaration* decl;

    //Instruction* functions;//non-main subroutines

    uint32_t ui32InstCount;
    Instruction* psInst;
} Shader;

#endif
