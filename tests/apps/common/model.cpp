#include <GL/glew.h>
#include "model.h"
#include "debug.h"
#include <fstream>


bool Model::Import3DFromFile( const std::string& pFile)
{
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

	mScene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if( !mScene)
	{
		OutputDebugString( importer.GetErrorString());
		return false;
	}

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

	CreateBuffers();

	return true;
}

void Model::CreateBuffers()
{
	const struct aiMesh* mesh = mScene->mMeshes[0];

	GLuint indicesBuf;
	uint32_t* indicesPtr;

	glGenBuffers(1, &indicesBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->mNumFaces * 3 * sizeof(uint32_t), NULL, GL_STATIC_DRAW);

	indicesPtr = static_cast<uint32_t*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

	for (uint32_t t = 0; t < mesh->mNumFaces; ++t) {
		const struct aiFace* face = &mesh->mFaces[t];

		ASSERT(face->mNumIndices == 3); //Triangles only.

		*indicesPtr++ = face->mIndices[0];
		*indicesPtr++ = face->mIndices[1];
		*indicesPtr++ = face->mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);


	uint32_t vertexCount = mesh->mNumVertices;
	uint32_t vertexFloats = 6;

	mHaveTexCoords = mesh->HasTextureCoords(0);

	if(mHaveTexCoords)
	{
		vertexFloats += 2;
	}

	GLuint verticesBuf;
	float* verticesPtr;
	glGenBuffers(1, &verticesBuf);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuf);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexFloats * sizeof(float), NULL, GL_STATIC_DRAW);

	verticesPtr = static_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	for(uint32_t vtx = 0; vtx < vertexCount; ++vtx)
	{
		*verticesPtr++ = mesh->mVertices[vtx].x;
		*verticesPtr++ = mesh->mVertices[vtx].y;
		*verticesPtr++ = mesh->mVertices[vtx].z;

		*verticesPtr++ = mesh->mNormals[vtx].x;
		*verticesPtr++ = mesh->mNormals[vtx].y;
		*verticesPtr++ = mesh->mNormals[vtx].z;

		if(mHaveTexCoords)
		{
			*verticesPtr++ = mesh->mTextureCoords[0][vtx].x;
			*verticesPtr++ = mesh->mTextureCoords[0][vtx].y;
		}
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	mIdxBuf = indicesBuf;
	mVtxBuf = verticesBuf;
	mVertexSize = vertexFloats * sizeof(float);
	mNumIndices = mesh->mNumFaces * 3;
}

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

void get_bounding_box_for_node (const aiScene* scene,
	const aiNode* nd, 
	 aiVector3D* min, 
	 aiVector3D* max, 
	 aiMatrix4x4* trafo
){
	 aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;

	*trafo = trafo[0] * nd->mTransformation;;

	for (; n < nd->mNumMeshes; ++n) {
		const  aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			 aiVector3D tmp = mesh->mVertices[t];

			tmp *= (*trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(scene, nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}

// ----------------------------------------------------------------------------
void get_bounding_box ( const aiScene* scene, aiVector3D* min,  aiVector3D* max)
{
	 aiMatrix4x4 trafo;

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene, scene->mRootNode,min,max,&trafo);
}

void Model::DrawR(ITransform& world, const  aiNode* nd)
{
	Vectormath::Aos::Matrix4 localWorld = world.GetWorldMatrix();

	aiMatrix4x4 m = nd->mTransformation;

	m.Transpose();

	for(int n =0; n < nd->mNumMeshes; ++n)
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
	
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		//glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mVertexSize, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mVertexSize, (void*)(sizeof(float)*3));
		/*if(mHaveTexCoords)
		{
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mVertexSize, (void*)(sizeof(float)*6));
		}*/

		world.SetWorldMatrix(localWorld);

		glDrawElements(GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);
	}

	// draw all children
	for (int n = 0; n < nd->mNumChildren; ++n) {
		DrawR(world, nd->mChildren[n]);
	}

	glPopMatrix();
}

void Model::Draw(ITransform& world)
{
	Vectormath::Aos::Matrix4 localWorld = world.GetWorldMatrix();
	Vectormath::Aos::Matrix4 originalWorld = localWorld;
	aiVector3D scene_min, scene_max, scene_center;

	get_bounding_box(mScene, &scene_min,&scene_max);
	scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
	scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
	scene_center.z = (scene_min.z + scene_max.z) / 2.0f;

	// scale the whole asset to fit into our view frustum 
	float tmp = scene_max.x-scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y,tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z,tmp);
	tmp = 1.f / tmp;

	localWorld *= Vectormath::Aos::Matrix4::scale(Vectormath::Aos::Vector3(tmp, tmp, tmp));

	localWorld *= Vectormath::Aos::Matrix4::translation(Vectormath::Aos::Vector3(-scene_center.x, -scene_center.y, -scene_center.z));

	glBindVertexArray(mVAO);

	world.SetWorldMatrix(localWorld);

	DrawR(world, mScene->mRootNode);

	world.SetWorldMatrix(originalWorld);
}

