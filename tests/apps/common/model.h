#include "assimp/Importer.hpp"
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"

#include <pstdint.h>
#include <vectormath_aos.h>

#include <Shader.h>
#include <itransform.h>

class Material
{
public:
    Material () : mTexID(0) {
    }
    void SetDiffuseTexture(const char* path);
    void Apply();
	void BindForLoadStore(GLenum access);

protected:
    unsigned int mTexID;
	GLenum mTexFormat;
};

class Model
{
public:
	bool Import3DFromFile( const std::string& pFile);
	void Draw(ITransform& World);
	Material& GetMaterial(){return mMaterial;}
	
protected:
	void RecursiveDraw(ITransform& World, const  aiNode* nd);
private:
	void CreateBuffers();
    void CreateMaterial();
	const aiScene* mScene;
	uint32_t mVtxBuf;
	uint32_t mIdxBuf;

	int mHaveTexCoords;
	int mVertexSize;
	int mNumIndices;

    Material mMaterial;

	Assimp::Importer importer;

    GLuint mVAO;
    GLuint indicesBuf;
    GLuint verticesBuf;
};
