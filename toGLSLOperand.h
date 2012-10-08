#ifndef TO_GLSL_OPERAND_H
#define TO_GLSL_OPERAND_H

#include "structs.h"

void TranslateOperand(const Operand* psOperand);
void TranslateSystemValueVariableName(const Operand* psOperand);
int GetMaxComponentFromComponentMask(const Operand* psOperand);
void TranslateIndex(const Operand* psOperand, int index);
void TranslateOperandSwizzle(const Operand* psOperand);

#endif
