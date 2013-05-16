#ifndef TO_GLSL_OPERAND_H
#define TO_GLSL_OPERAND_H

#include "structs.h"

#define TO_FLAG_NONE    0x0
#define TO_FLAG_INTEGER 0x1
#define TO_FLAG_NAME_ONLY 0x2
#define TO_FLAG_DECLARATION_NAME 0x4
void TranslateOperand(HLSLCrossCompilerContext* psContext, const Operand* psOperand, uint32_t ui32TOFlag);

int GetMaxComponentFromComponentMask(const Operand* psOperand);
void TranslateOperandIndex(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index);
void TranslateOperandIndexMAD(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index, uint32_t multiply, uint32_t add);
void TranslateOperandSwizzle(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
uint32_t GetNumSwizzleElements(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
void AddSwizzleUsingElementCount(HLSLCrossCompilerContext* psContext, uint32_t count);
int GetFirstOperandSwizzle(HLSLCrossCompilerContext* psContext, const Operand* psOperand);

void TextureName(HLSLCrossCompilerContext* psContext, const uint32_t ui32RegisterNumber, const int bZCompare);

//Non-zero means the components overlap
int CompareOperandSwizzles(const Operand* psOperandA, const Operand* psOperandB);

#endif
