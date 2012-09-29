#ifndef TO_GLSL_H
#define TO_GLSL_H

#ifndef GL_VERTEX_SHADER_ARB
#define GL_VERTEX_SHADER_ARB              0x8B31
#endif
#ifndef GL_FRAGMENT_SHADER_ARB
#define GL_FRAGMENT_SHADER_ARB            0x8B30
#endif

typedef struct
{
    int shaderType;
    char* sourceCode;
} GLSLShader;

int TranslateHLSLFromFile(const char* filename, GLSLShader* result);
void TranslateHLSLFromMem(const char* shader, GLSLShader* result);

#endif
