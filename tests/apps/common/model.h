#include "assimp/Importer.hpp"
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"

#include <pstdint.h>

class Model
{
public:
	bool Import3DFromFile( const std::string& pFile);
	void Draw();
private:
	void CreateBuffers();
	const aiScene* mScene;
	uint32_t mVtxBuf;
	uint32_t mIdxBuf;

	int mHaveTexCoords;
	int mVertexSize;
	int mNumIndices;
};
