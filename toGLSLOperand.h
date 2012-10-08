#ifndef TO_GLSL_OPERAND_H
#define TO_GLSL_OPERAND_H

#include "structs.h"

void TranslateOperand(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
void TranslateSystemValueVariableName(HLSLCrossCompilerContext* psContext, const Operand* psOperand);
int GetMaxComponentFromComponentMask(const Operand* psOperand);
void TranslateIndex(HLSLCrossCompilerContext* psContext, const Operand* psOperand, int index);
void TranslateOperandSwizzle(HLSLCrossCompilerContext* psContext, const Operand* psOperand);

#endif
