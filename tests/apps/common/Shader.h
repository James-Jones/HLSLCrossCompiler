extern "C" {
#include "toGLSL.h"
#include "languages.h"
}

#include <string>
#include <pstdint.h>
typedef unsigned int uint_t;

class ShaderEffect
{
public:
    ShaderEffect();

    void Create();

    //Bitwise OR of the HLSLCC_FLAG_ values
    //defined in toGLSL.h
    void SetCompileFlags(uint_t flags) {
        mCompileFlags = flags;
    }

    void SetLanguage(GLLang lang) {
        mLang = lang;
    }

    void FromByteFile(std::string& path);
    void FromVertexByteFile(std::string& path);
    void FromPixelByteFile(std::string& path);

    void Enable();

    //GLuint GetVariableByName(std::string* name);

    void SetVec4(std::string& name, int count, float* v);
    void SetUniformBlock(std::string& name, uint_t bufIndex);
    void SetUniformBlock(std::string& name, uint_t bufIndex, uint_t ubo);

    uint_t VS() const {
        return mVertex;
    }
    uint_t PS() const {
        return mPixel;
    }
    uint_t Language() const {
        return mLang;
    }
    uint_t CompileFlags() const {
        return mCompileFlags;
    }
protected:

private:
    GLLang mLang;
    uint_t mCompileFlags;
    uint_t mProgram;
    uint_t mVertex;
    uint_t mPixel;
};

