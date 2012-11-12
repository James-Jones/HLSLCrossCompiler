#include "model.h"
#include "debug.h"
#include <fstream>

bool Model::Import3DFromFile( const std::string& pFile)
{
	Assimp::Importer importer;

	//check if file exists
	std::ifstream fin(pFile.c_str());
	if(!fin.fail())
	{
		fin.close();
	}
	else
	{
		OutputDebugString( importer.GetErrorString());
		return false;
	}

	scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if( !scene)
	{
		OutputDebugString( importer.GetErrorString());
		return false;
	}
	return true;
}

