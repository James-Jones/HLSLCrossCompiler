#ifndef SHADER_H_
#define SHADER_H_

extern "C" {
#include "toGLSL.h"
}

#include <string>
#include "pstdint.h"
typedef unsigned int uint_t;

#include <vectormath_aos.h>

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

    void FromGLSLFile(uint_t eShaderType, std::string& path);

    void Enable();

	void CreateUniformBlock(std::string& name, uint_t& ubo);

    void SetTexture(std::string& name, int imageUnit);
    void SetVec4(std::string& name, int count, float* v);
    void SetUniformBlock(std::string& name, uint_t bufIndex);
    void SetUniformBlock(std::string& name, uint_t bufIndex, uint_t ubo);

    uint_t VS() const {
        return mVertex;
    }
    uint_t PS() const {
        return mPixel;
    }
    uint_t GS() const {
        return mGeometry;
    }
    uint_t HS() const {
        return mHull;
    }
    uint_t DS() const {
        return mDomain;
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
	uint_t mGeometry;
    uint_t mHull;
    uint_t mDomain;
};

static void SetFloatArray(Vectormath::Aos::Vector4& vec, float* farray)
{
    farray[0] = vec.getX();
    farray[1] = vec.getY();
    farray[2] = vec.getZ();
    farray[3] = vec.getW();
}
static void SetFloatArray(Vectormath::Aos::Matrix4& matrix, float* farray)
{
    for(int row = 0; row < 4; row++)
    {
        Vectormath::Aos::Vector4 r = matrix.getRow(row);
        SetFloatArray(r, &farray[row*4]);
    }
}

#endif