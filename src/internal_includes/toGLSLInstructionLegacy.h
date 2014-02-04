#ifndef TO_GLSL_INSTRUCTION_H

#include "internal_includes/structs.h"

void TranslateInstructionLegacy(HLSLCrossCompilerContext* psContext, Instruction* psInst);

void SetDataTypesLegacy(HLSLCrossCompilerContext* psContext, Instruction* psInst, const int32_t i32InstCount);

#endif
