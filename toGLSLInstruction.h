#ifndef TO_GLSL_INSTRUCTION_H

#include "structs.h"

void TranslateInstruction(HLSLCrossCompilerContext* psContext, Instruction* psInst);

//For each MOV temp, immediate; check to see if the next instruction
//using dest has an integer opcode. If so then the immediate value
//is flaged as having an integer encoding.
void MarkIntegerImmediates(HLSLCrossCompilerContext* psContext);

#endif
