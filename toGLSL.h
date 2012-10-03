#ifndef TO_GLSL_H
#define TO_GLSL_H

#include "languages.h"

typedef struct
{
    int shaderType; //One of the GL enums.
    char* sourceCode;
} GLSLShader;

int TranslateHLSLFromFile(const char* filename, GLLang language, GLSLShader* result);
void TranslateHLSLFromMem(const char* shader, GLLang language, GLSLShader* result);

#endif
