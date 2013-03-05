#ifndef TO_GLSL_OPERAND_H
#define TO_GLSL_OPERAND_H

#include "structs.h"

void TranslateOperand(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
void TranslateIntegerOperand(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
void TranslateSystemValueVariableName(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
int GetMaxComponentFromComponentMask(const Operand* psOperand);
void TranslateOperandIndex(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index);
void TranslateOperandIndexMAD(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index, uint32_t multiply, uint32_t add);
void TranslateOperandSwizzle(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
uint32_t GetNumSwizzleElements(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
void AddSwizzleUsingElementCount(HLSLCrossCompilerContext* psContext, uint32_t count);

void TextureName(HLSLCrossCompilerContext* psContext, const uint32_t ui32RegisterNumber, const int bZCompare);

//Non-zero means the components overlap
int CompareOperandSwizzles(const Operand* psOperandA, const Operand* psOperandB);

#endif
