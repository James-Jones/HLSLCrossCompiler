#ifndef TO_GLSL_DECLARATION_H
#define TO_GLSL_DECLARATION_H

#include "internal_includes/structs.h"

void TranslateDeclaration(HLSLCrossCompilerContext* psContext, const Declaration* psDecl);

const char* GetDeclaredName(const HLSLCrossCompilerContext* psContext, const SHADER_TYPE eShaderType, const Operand* psOperand);

//Hull shaders have multiple phases.
//Each phase has its own temps.
//Convert to global temps for GLSL.
void ConsolidateHullTempVars(Shader* psShader);

#endif
