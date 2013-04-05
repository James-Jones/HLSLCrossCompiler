#ifndef TO_GLSL_DECLARATION_H
#define TO_GLSL_DECLARATION_H

#include "structs.h"

void TranslateDeclaration(HLSLCrossCompilerContext* psContext, const Declaration* psDecl);

const char* GetDeclaredName(SHADER_TYPE eShaderType, unsigned int flags);

//Hull shaders have multiple phases.
//Each phase has its own temps.
//Convert to global temps for GLSL.
void ConsolidateHullTempVars(Shader* psShader);

#endif
