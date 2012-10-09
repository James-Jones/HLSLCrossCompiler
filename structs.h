#ifndef STRUCTS_H
#define STRUCTS_H

#include "tokens.h"
#include "languages.h"
#include "bstrlib.h"

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

    uint32_t aui32ArraySizes[3];
    uint32_t ui32RegisterNumber;
    //If eType is OPERAND_TYPE_IMMEDIATE32
    float afImmediates[4];
    //uint64_t aui64Immediates;

    SPECIAL_NAME eSpecialName;
    char pszSpecialName[64];

    OPERAND_INDEX_REPRESENTATION eIndexRep[3];

    struct Operand_TAG* psSubOperand[3];

#ifdef _DEBUG
    uint64_t id;
#endif
} Operand;

typedef struct Instruction_TAG
{
    OPCODE_TYPE eOpcode;
    INSTRUCTION_TEST_BOOLEAN eBooleanTestType;
    uint32_t ui32NumOperands;
    Operand asOperands[4];

#ifdef _DEBUG
    uint64_t id;
#endif
} Instruction;

typedef struct Declaration_TAG
{
    OPCODE_TYPE eOpcode;

    uint32_t ui32NumOperands;
    Operand asOperands[1];

    //The declaration can set one of these
    //values depending on the opcode.
    union {
        uint32_t ui32GlobalFlags;
        uint32_t ui32NumTemps;
        RESOURCE_DIMENSION eResourceDimension;
        INTERPOLATION_MODE eInterpolation;
        PRIMITIVE_TOPOLOGY eOutputPrimitiveTopology;
        PRIMITIVE eInputPrimitive;
        uint32_t ui32MaxOutputVertexCount;
        TESSELLATOR_DOMAIN eTessDomain;
        TESSELLATOR_PARTITIONING eTessPartitioning;
        TESSELLATOR_OUTPUT_PRIMITIVE eTessOutPrim;
        uint32_t aui32WorkGroupSize[3];
    } value;
} Declaration;

typedef struct Shader_TAG
{
    uint32_t ui32MajorVersion;
    uint32_t ui32MinorVersion;
    SHADER_TYPE eShaderType;

    GLLang eTargetLanguage;

    //DWORDs in program code, including version and length tokens.
    uint32_t ui32ShaderLength;

    uint32_t ui32DeclCount;
    Declaration* psDecl;

    //Instruction* functions;//non-main subroutines

    uint32_t ui32InstCount;
    Instruction* psInst;
} Shader;

//typedef __restrict struct tagbstring * restrict_bstring;

typedef struct HLSLCrossCompilerContext_TAG
{
    bstring glsl;
    int indent;
    unsigned int flags;
    Shader* psShader;
} HLSLCrossCompilerContext;

#endif
