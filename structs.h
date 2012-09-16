#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Operand_TAG
{
    int iExtended;
    OPERAND_TYPE eType;
    OPERAND_MODIFIER eModifier;
    int iIndexDims;
    int indexRepresentation[4];
    int writeMask;
    int iGSInput;
    int iWriteMaskEnabled;

    int iNumComponents;

    OPERAND_4_COMPONENT_SELECTION_MODE eSelMode;
    uint32_t ui32CompMask;
    uint32_t ui32Swizzle;
    uint32_t aui32Swizzle[4];

    uint32_t ui32RegisterNumber;
    //If eType is OPERAND_TYPE_IMMEDIATE32
    float afImmediates[4];
    //uint64_t aui64Immediates;


    SPECIAL_NAME eSpecialName;
    char pszSpecialName[64];
} Operand;

typedef struct Instruction_TAG
{
    OPCODE_TYPE eOpcode;
    INSTRUCTION_TEST_BOOLEAN eBooleanTestType;
    uint32_t ui32NumOperands;
    Operand asOperands[4];
} Instruction;

typedef struct Declaration_TAG
{
    OPCODE_TYPE eOpcode;
    uint32_t ui32GlobalFlags;
    uint32_t ui32NumOperands;
    uint32_t ui32NumTemps;
    RESOURCE_DIMENSION eResourceDimension;
    INTERPOLATION_MODE eInterpolation;
    PRIMITIVE_TOPOLOGY ePrimitiveTopology;
    Operand asOperands[1];
} Declaration;

typedef struct Shader_TAG
{
    uint32_t ui32MajorVersion;
    uint32_t ui32MinorVersion;
    SHADER_TYPE eShaderType;

    //DWORDs in program code, including version and length tokens.
    uint32_t ui32ShaderLength;

    uint32_t ui32DeclCount;
    Declaration* psDecl;

    //Instruction* functions;//non-main subroutines

    uint32_t ui32InstCount;
    Instruction* psInst;
} Shader;

#endif
