#include "assimp/Importer.hpp"
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"

#include <pstdint.h>
#include <vectormath_aos.h>

#include <Shader.h>
#include <itransform.h>

class Model
{
public:
	bool Import3DFromFile( const std::string& pFile);
	void Draw(ITransform& World);
	
protected:
	void DrawR(ITransform& World, const  aiNode* nd);
private:
	void CreateBuffers();
	const aiScene* mScene;
	uint32_t mVtxBuf;
	uint32_t mIdxBuf;

	int mHaveTexCoords;
	int mVertexSize;
	int mNumIndices;

	Assimp::Importer importer;

    GLuint mVAO;
};
