#include "Shader.h"
#include <GL/glew.h>
#include "common/debug.h"

const uint_t InvalidShaderHandle = 0xFFFFFFFF;

ShaderEffect::ShaderEffect() : mCompileFlags(0), mRequestedLang(LANG_DEFAULT),
    mVertex(InvalidShaderHandle),
    mPixel(InvalidShaderHandle),
    mGeometry(InvalidShaderHandle),
    mHull(InvalidShaderHandle),
    mDomain(InvalidShaderHandle),
	mCompute(InvalidShaderHandle),
    mClipDistanceMaskVS(0),
    mClipDistanceMaskGS(0),
    mProgram(0)
{
}

ShaderEffect::~ShaderEffect()
{
    if(mProgram)
    {
        glDeleteProgram(mProgram);//Auto detaches all shaders.
    }
    if(mVertex != InvalidShaderHandle)
    {
        glDeleteShader(mVertex);
    }
    if(mPixel != InvalidShaderHandle)
    {
        glDeleteShader(mPixel);
    }
    if(mGeometry != InvalidShaderHandle)
    {
        glDeleteShader(mGeometry);
    }
    if(mHull != InvalidShaderHandle)
    {
        glDeleteShader(mHull);
    }
    if(mDomain != InvalidShaderHandle)
    {
        glDeleteShader(mHull);
    }
	if(mCompute != InvalidShaderHandle)
	{
		glDeleteShader(mCompute);
	}
}

static int HaveLimitedInOutLocationQualifier(const GLLang eLang)
{
    if(eLang >= LANG_330 || eLang == LANG_ES_300)
    {
        return 1;
    }
    return 0;
}

void ShaderEffect::Create()
{
    mProgram = glCreateProgram();

    if(HaveLimitedInOutLocationQualifier(mVSLang) == 0 || HaveLimitedInOutLocationQualifier(mPSLang) == 0)
    {
        int maxAttrib = 0;

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttrib);

        for(int i=0; i<maxAttrib; ++i)
        {
            std::string attribName("dcl_Input");
            //Visual Studio/Windows missing int version std::to_string, so use long long.
            attribName += std::to_string((long long)i);

            glBindAttribLocation(mProgram, i, attribName.c_str());
        }

        int maxDrawBuffers = 0;

        glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers);

        for(int i=0; i<maxAttrib; ++i)
        {
            std::string pixelOutputName("PixOutput");
            pixelOutputName += std::to_string((long long)i);

            glBindFragDataLocation(mProgram, i, pixelOutputName.c_str());
        }
    }
}

void ShaderEffect::FromGLSLFile(uint_t eShaderType, std::string& path)
{

    char* shaderSrc;

    {
        FILE* shaderFile;
        int length;
        int readLength;
	    int success = 0;

        shaderFile = fopen(path.c_str(), "rb");

        ASSERT(shaderFile);

        fseek(shaderFile, 0, SEEK_END);
        length = ftell(shaderFile);
        fseek(shaderFile, 0, SEEK_SET);

        shaderSrc = (char*)malloc(length+1);

        readLength = fread(shaderSrc, 1, length, shaderFile);

        fclose(shaderFile);
        shaderFile = 0;

        shaderSrc[readLength] = '\0';
    }

    uint_t shader = 0;

    switch(eShaderType)
    {
        case GL_VERTEX_SHADER:
        {
            mVertex = glCreateShader(GL_VERTEX_SHADER);
            shader = mVertex;
            mVSLang = LANG_DEFAULT;
            break;
        }
        case GL_FRAGMENT_SHADER:
        {
            mPixel = glCreateShader(GL_FRAGMENT_SHADER);
            shader = mPixel;
            mPSLang = LANG_DEFAULT;
            break;
        }
        case GL_GEOMETRY_SHADER:
        {
            mGeometry = glCreateShader(GL_GEOMETRY_SHADER);
            shader = mGeometry;
            mGSLang = LANG_DEFAULT;
            break;
        }
        case GL_TESS_CONTROL_SHADER:
        {
            mHull = glCreateShader(GL_TESS_CONTROL_SHADER);
            shader = mHull;
            mHSLang = LANG_DEFAULT;
            break;
        }
        case GL_TESS_EVALUATION_SHADER:
        {
            mDomain = glCreateShader(GL_TESS_EVALUATION_SHADER);
            shader = mDomain;
            mDSLang = LANG_DEFAULT;
            break;
        }
        case GL_COMPUTE_SHADER:
        {
            mCompute = glCreateShader(GL_COMPUTE_SHADER);
            shader = mCompute;
            mCSLang = LANG_DEFAULT;
            break;
        }
        default:
        {
            break;
        }
    }

    glShaderSource(shader, 1, (const char **)&shaderSrc, 0);
    glCompileShader(shader);
    glAttachShader(mProgram, shader);

#ifdef _DEBUG
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        char* log;
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        log = new char[length];
        glGetShaderInfoLog(shader, length, NULL, log);
        ASSERT(0);
        delete [] log;

        ASSERT(0);
    }
#endif

    delete [] shaderSrc;
}

static int PixelInterpDependency(const GLLang eLang)
{
    if(eLang < LANG_430)
    {
        return 1;
    }
    return 0;
}

void ShaderEffect::FromByteFile(std::string& path)
{
    GLSLShader result;

    int translated = TranslateHLSLFromFile(path.c_str(), mCompileFlags, mRequestedLang,NULL, &mDependencies, &result);

    ASSERT(translated);

    uint_t shader = 0;

#if 0 //Disabled to allow running with only a vertex shader + rasterizer discard.
    if(PixelInterpDependency(result.GLSLLanguage))
    {
        //Must compile pixel shader first!
        if(mPixel == InvalidShaderHandle &&  result.shaderType != GL_FRAGMENT_SHADER)
        {
            ASSERT(0);
        }
    }
#endif

    switch(result.shaderType)
    {
        case GL_VERTEX_SHADER:
        {
            mVertex = glCreateShader(GL_VERTEX_SHADER);
            shader = mVertex;
            mVSLang = result.GLSLLanguage;
            break;
        }
        case GL_FRAGMENT_SHADER:
        {
            mPixel = glCreateShader(GL_FRAGMENT_SHADER);
            shader = mPixel;
            mPSLang = result.GLSLLanguage;
            break;
        }
        case GL_GEOMETRY_SHADER:
        {
            mGeometry = glCreateShader(GL_GEOMETRY_SHADER);
            shader = mGeometry;
            mGSLang = result.GLSLLanguage;
            break;
        }
        case GL_TESS_CONTROL_SHADER:
        {
            mHull = glCreateShader(GL_TESS_CONTROL_SHADER);
            shader = mHull;
            mHSLang = result.GLSLLanguage;
            break;
        }
        case GL_TESS_EVALUATION_SHADER:
        {
            mDomain = glCreateShader(GL_TESS_EVALUATION_SHADER);
            shader = mDomain;
            mDSLang = result.GLSLLanguage;

            //Hull shader must be compiled before domain in order
            //to ensure correct partitioning and primitive type information
            //is OR'ed into mCompileFlags.
            ASSERT(mHull != InvalidShaderHandle);

            break;
        }
        case GL_COMPUTE_SHADER:
        {
            mCompute = glCreateShader(GL_COMPUTE_SHADER);
            shader = mCompute;
            mCSLang = result.GLSLLanguage;
            break;
        }
        default:
        {
            break;
        }
    }

    CheckStateRequirements(result.shaderType, &result.reflection);

    glShaderSource(shader, 1, (const char **)&result.sourceCode, 0);
    glCompileShader(shader);
    glAttachShader(mProgram, shader);

#ifdef _DEBUG
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        char* log;
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        log = new char[length];
        glGetShaderInfoLog(shader, length, NULL, log);
        ASSERT(0);
        delete [] log;

        ASSERT(0);
    }
#endif


#if 0
    //Set the default values for constants.
    for(uint32_t i = 0; i < result.reflection.ui32NumConstantBuffers; ++i)
    {
        ConstantBuffer* cbuf = result.reflection.psConstantBuffers+i;

        for(uint32_t k = 0; k < cbuf->ui32NumVars; ++k)
        {
            uint32_t loc = glGetUniformLocation(mProgram, cbuf->asVars[k].Name);
            glUniform1f(loc, *(float*)&cbuf->asVars[k].ui32DefaultValue);
        }
    }
#endif

    FreeGLSLShader(&result);
}

void ShaderEffect::SetSubroutineUniforms(uint_t shaderType, SubroutineLink* link, int numLinks)
{
    int maxUniforms;
    glGetProgramStageiv(mProgram, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &maxUniforms);

    ASSERT(maxUniforms < MAX_SHADER_SUBROUTINES);

    for(int uniform = 0; uniform < maxUniforms; ++uniform)
    {
        if(uniform < numLinks)
        {
            SubroutineLink* ci = &link[uniform];

            const int uniformIndex = glGetSubroutineUniformLocation(mProgram, shaderType, ci->UniformName);

            const int functionIndex = glGetSubroutineIndex(mProgram, shaderType, ci->FunctionName);

            mSubroutineMap[uniformIndex] = functionIndex;
        }
    }

    glUniformSubroutinesuiv(shaderType, maxUniforms, mSubroutineMap);
}

void ShaderEffect::ApplyGLState()
{
	if(mCompute != InvalidShaderHandle)
	{
		//Compute state
		return;
	}

	//Graphics state

    if(mClipDistanceMaskGS)
    {
        int plane;
        for(plane = 0; plane < 8; ++plane)
        {
            if(mClipDistanceMaskGS & (1<<plane))
            {
                glEnable(GL_CLIP_DISTANCE0+plane);
            }
            else
            {
                glDisable(GL_CLIP_DISTANCE0+plane);
            }
        }
    }
    else if(mClipDistanceMaskVS)
    {
        int plane;
        for(plane = 0; plane < 8; ++plane)
        {
            if(mClipDistanceMaskVS & (1<<plane))
            {
                glEnable(GL_CLIP_DISTANCE0+plane);
            }
            else
            {
                glDisable(GL_CLIP_DISTANCE0+plane);
            }
        }
    }
    else
    {
        int plane;
        for(plane = 0; plane < 8; ++plane)
        {
            glDisable(GL_CLIP_DISTANCE0+plane);
        }
    }
}

void ShaderEffect::SetTransformFeedback(const int count, const char * const *varyings)
{
	glTransformFeedbackVaryings(mProgram, count, varyings, GL_INTERLEAVED_ATTRIBS);
}

void ShaderEffect::Link()
{
    glLinkProgram(mProgram);

#ifdef _DEBUG
    GLint linked = GL_FALSE;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        char* log;
        GLint length = 0;
        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length);
        log = new char[length];
        glGetProgramInfoLog(mProgram, length, NULL, log);
        ASSERT(0);
        delete [] log;
    }
#endif
}

void ShaderEffect::Enable()
{
    ApplyGLState();

    glUseProgram(mProgram);
}

void ShaderEffect::SetTexture(const char* name, int imageUnit) {
    int loc = glGetUniformLocation(mProgram, name);
    glUniform1i(loc, imageUnit);
}

void ShaderEffect::SetTexture(std::string& name, int imageUnit) {
    int loc = glGetUniformLocation(mProgram, (name).c_str());
    glUniform1i(loc, imageUnit);
}

void ShaderEffect::SetVec4(std::string& name, int count, float* v) {
    int loc = glGetUniformLocation(mProgram, name.c_str());
    glUniform4fv(loc, count, v);
}

void ShaderEffect::SetVec3(std::string& name, int count, float* v) {
    int loc = glGetUniformLocation(mProgram, name.c_str());
    glUniform3fv(loc, count, v);
}

void ShaderEffect::SetFloat(std::string& name, int count, float* v) {
    int loc = glGetUniformLocation(mProgram, name.c_str());
    glUniform1fv(loc, count, v);
}

void ShaderEffect::CreateUniformBlock(std::string& name, uint_t& ubo)
{
	GLuint bufferID;

    glGenBuffers(1, &bufferID);

    uint_t uniformBlockIndex = glGetUniformBlockIndex(mProgram, name.c_str());
        
	GLint uniformBlockSize;
    //We need to get the uniform block's size in order to back it with the
    //appropriate buffer
    glGetActiveUniformBlockiv(mProgram, uniformBlockIndex,
                                    GL_UNIFORM_BLOCK_DATA_SIZE,
                                    &uniformBlockSize);

    //Create UBO.
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
    glBufferData(GL_UNIFORM_BUFFER, uniformBlockSize,
                    NULL, GL_DYNAMIC_DRAW);

	ubo = bufferID;
}

void ShaderEffect::SetUniformBlock(std::string& name, uint_t bufIndex)
{
    int uniformIndex = glGetUniformBlockIndex(mProgram, (name).c_str());
    glUniformBlockBinding(mProgram, uniformIndex, bufIndex);
}

void ShaderEffect::SetUniformBlock(std::string& name, uint_t bufIndex, uint_t ubo)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bufIndex, ubo);
	SetUniformBlock(name, bufIndex);
}

static int GetOutputSignatureFromSystemValue(SPECIAL_NAME eSystemValueType, uint32_t ui32SemanticIndex, ShaderInfo* psShaderInfo, InOutSignature** ppsOut)
{
    uint32_t i;
    const uint32_t ui32NumVars = psShaderInfo->ui32NumOutputSignatures;

    for(i=0; i<ui32NumVars; ++i)
    {
        InOutSignature* psOutputSignatures = psShaderInfo->psOutputSignatures;
        if(eSystemValueType == psOutputSignatures[i].eSystemValueType &&
            ui32SemanticIndex == psOutputSignatures[i].ui32SemanticIndex)
	    {
		    *ppsOut = psOutputSignatures+i;
		    return 1;
	    }
    }
    return 0;
}
void ShaderEffect::CheckStateRequirements(uint_t eShaderType, ShaderInfo* reflection)
{
    const uint32_t count = reflection->ui32NumOutputSignatures;
    InOutSignature* psClipSignature;
    uint_t nextPlane = 0;
    
    if(GetOutputSignatureFromSystemValue(NAME_CLIP_DISTANCE, 0, reflection, &psClipSignature))
    {
        if(eShaderType == GL_VERTEX_SHADER)
        {
            mClipDistanceMaskVS |= psClipSignature->ui32Mask;
        }
        else if(eShaderType == GL_GEOMETRY_SHADER)
        {
            mClipDistanceMaskGS |= psClipSignature->ui32Mask;
        }
    }
    if(GetOutputSignatureFromSystemValue(NAME_CLIP_DISTANCE, 1, reflection, &psClipSignature))
    {
        if(eShaderType == GL_VERTEX_SHADER)
        {
            mClipDistanceMaskVS |= psClipSignature->ui32Mask<<4;
        }
        else if(eShaderType == GL_GEOMETRY_SHADER)
        {
            mClipDistanceMaskGS |= psClipSignature->ui32Mask<<4;
        }
    }
}

