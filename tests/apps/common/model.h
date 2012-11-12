#include "assimp/Importer.hpp"
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"

class Model
{
public:
	bool Import3DFromFile( const std::string& pFile);
private:
	const aiScene* scene;
};
