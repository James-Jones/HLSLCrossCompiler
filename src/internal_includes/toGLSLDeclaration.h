#ifndef TO_GLSL_DECLARATION_H
#define TO_GLSL_DECLARATION_H

#include "internal_includes/structs.h"

void TranslateDeclaration(HLSLCrossCompilerContext* psContext, const Declaration* psDecl);

const char* GetDeclaredInputName(const HLSLCrossCompilerContext* psContext, const SHADER_TYPE eShaderType, const Operand* psOperand);
const char* GetDeclaredOutputName(const HLSLCrossCompilerContext* psContext, const SHADER_TYPE eShaderType, const Operand* psOperand, int* stream);

//Hull shaders have multiple phases.
//Each phase has its own temps.
//Convert to global temps for GLSL.
void ConsolidateHullTempVars(Shader* psShader);
void TranslateDeclaration_HS_NoControlPointStage(HLSLCrossCompilerContext* psContext);

#endif
