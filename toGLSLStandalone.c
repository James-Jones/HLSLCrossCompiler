
#include "toGLSL.h"
#include "languages.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define VALIDATE_OUTPUT

#if defined(VALIDATE_OUTPUT) && defined(_WIN32)
#if defined(_WIN32)
#include <windows.h>
#include <gl/GL.h>

 #pragma comment(lib, "opengl32.lib")

	typedef char GLcharARB;		/* native character */
	typedef unsigned int GLhandleARB;	/* shader object handle */
#define GL_VERTEX_SHADER_ARB              0x8B31
#define GL_FRAGMENT_SHADER_ARB            0x8B30
#define GL_OBJECT_COMPILE_STATUS_ARB      0x8B81
#define GL_OBJECT_LINK_STATUS_ARB         0x8B82
	typedef void (WINAPI * PFNGLDELETEOBJECTARBPROC) (GLhandleARB obj);
	typedef GLhandleARB (WINAPI * PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
	typedef void (WINAPI * PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, const GLcharARB* *string, const GLint *length);
	typedef void (WINAPI * PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
	typedef void (WINAPI * PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
	typedef void (WINAPI * PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint *params);
	typedef GLhandleARB (WINAPI * PFNGLCREATEPROGRAMOBJECTARBPROC) (void);
	typedef void (WINAPI * PFNGLATTACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB obj);
	typedef void (WINAPI * PFNGLLINKPROGRAMARBPROC) (GLhandleARB programObj);
	typedef void (WINAPI * PFNGLUSEPROGRAMOBJECTARBPROC) (GLhandleARB programObj);
    //typedef void (WINAPI * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* param);
    typedef void (WINAPI * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei* length, GLcharARB* infoLog);

	static PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
	static PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
	static PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
	static PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
	static PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
	static PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
	static PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
	static PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
	static PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
	static PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
    //static PFNGLGETSHADERIVPROC glGetShaderiv;
    static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

void InitOpenGL()
{
    HGLRC rc;

	// setup minimal required GL
	HWND wnd = CreateWindowA(
							 "STATIC",
							 "GL",
							 WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
							 0, 0, 16, 16,
							 NULL, NULL,
							 GetModuleHandle(NULL), NULL );
	HDC dc = GetDC( wnd );
	
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA, 32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		16, 0,
		0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};
	
	int fmt = ChoosePixelFormat( dc, &pfd );
	SetPixelFormat( dc, fmt, &pfd );
	
	rc = wglCreateContext( dc );
	wglMakeCurrent( dc, rc );

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if(wglCreateContextAttribsARB)
    {
        const int OpenGLContextAttribs [] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    #if defined(_DEBUG)
            //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
    #else
            //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    #endif
            //WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0, 0
        };

        const HGLRC OpenGLContext = wglCreateContextAttribsARB( dc, 0, OpenGLContextAttribs );

        wglMakeCurrent(dc, OpenGLContext);

        wglDeleteContext(rc);

        rc = OpenGLContext;
    }

    glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)wglGetProcAddress("glDeleteObjectARB");
    glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
    glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB");
    glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB");
    glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
    glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
    glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)wglGetProcAddress("glCreateProgramObjectARB");
    glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)wglGetProcAddress("glAttachObjectARB");
    glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB");
    glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)wglGetProcAddress("glUseProgramObjectARB");
    //glGetShaderiv = (PFNGLGETSHADERIVPROC)("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)("glGetShaderInfoLog");
}
#endif

int TryCompileShader(GLenum eGLSLShaderType, char* shader)
{
    GLint iCompileStatus;
    GLuint hShader;

    InitOpenGL();

    hShader = glCreateShaderObjectARB(eGLSLShaderType);
    glShaderSourceARB(hShader, 1, (const char **)&shader, NULL);

    glCompileShaderARB(hShader);

    /* Check it compiled OK */
    glGetObjectParameterivARB (hShader, GL_OBJECT_COMPILE_STATUS_ARB, &iCompileStatus);
    //glGetShaderiv(hShader, GL_COMPILE_STATUS, &iCompileStatus); 

    if (iCompileStatus != GL_TRUE)
    {
        FILE* errorFile;
        GLint iInfoLogLength = 0;
        char pszInfoLog[1024];

        printf("Error: Failed to compile GLSL shader\n");

		//char log[4096];
		//GLsizei logLength;
		glGetInfoLogARB (hShader, sizeof(pszInfoLog), &iInfoLogLength, pszInfoLog);

        //glGetShaderInfoLog(hShader, 1024, &iInfoLogLength, pszInfoLog);
        printf(pszInfoLog);

        //Dump to file
        errorFile = fopen("compileErrors.txt", "w");
        fprintf(errorFile, pszInfoLog);
        fclose(errorFile);

        return 0;
    }

    printf("Shader compiled successfully\n");

    return 1;
}
#endif

int fileExists(const char* path)
{
    FILE* shaderFile;
    shaderFile = fopen(path, "rb");

    if(shaderFile)
    {
        fclose(shaderFile);
        return 1;
    }
    return 0;
}

GLLang LanguageFromString(const char* str)
{
    if(strcmp(str, "es100")==0)
    {
        return LANG_ES_100;
    }
    if(strcmp(str, "es300")==0)
    {
        return LANG_ES_300;
    }
    if(strcmp(str, "120")==0)
    {
        return LANG_120;
    }
    if(strcmp(str, "130")==0)
    {
        return LANG_130;
    }
    if(strcmp(str, "140")==0)
    {
        return LANG_140;
    }
    if(strcmp(str, "150")==0)
    {
        return LANG_150;
    }
    if(strcmp(str, "330")==0)
    {
        return LANG_330;
    }
    if(strcmp(str, "400")==0)
    {
        return LANG_400;
    }
    if(strcmp(str, "410")==0)
    {
        return LANG_410;
    }
    if(strcmp(str, "420")==0)
    {
        return LANG_420;
    }
    if(strcmp(str, "430")==0)
    {
        return LANG_430;
    }
    return LANG_DEFAULT;
}

void main(int argc, char** argv)
{
    FILE* outputFile;
    GLSLShader result;
    GLLang language = LANG_DEFAULT;

    printf("args: bytecode-file [output-file] [language override - es100 es300 120 130 etc.]\n");

    if(argc < 2 || !fileExists(argv[1]))
    {
        printf("Bad args. Supply a valid shader path, optionaly followed by the output path\n");
        return;
    }

    if(argc > 3)
    {
        language = LanguageFromString(argv[3]);
    }

    if(TranslateHLSLFromFile(argv[1], 0, language, &result))
    {
        if(argc > 2)
        {
            //Dump to file
            outputFile = fopen(argv[2], "w");
            fprintf(outputFile, result.sourceCode);
            fclose(outputFile);
        }

#if defined(VALIDATE_OUTPUT)
        TryCompileShader(result.shaderType, result.sourceCode);
#endif

        bcstrfree(result.sourceCode);
    }
}
