#include <GL/glew.h>
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

	mScene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if( !mScene)
	{
		OutputDebugString( importer.GetErrorString());
		return false;
	}

	CreateBuffers();

	return true;
}

void Model::CreateBuffers()
{
	//const struct aiNode* nd = mScene->mRootNode;
	const struct aiMesh* mesh = mScene->mMeshes[0];//nd->mMeshes[0]];

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
	//mesh->mVertices

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
	mVertexSize = vertexFloats;
	mNumIndices = mesh->mNumFaces;
}

void Model::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, mVtxBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIdxBuf);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mVertexSize, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mVertexSize, (void*)(sizeof(float)*3));
	if(mHaveTexCoords)
	{
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mVertexSize, (void*)(sizeof(float)*6));
	}

	glDrawElements(GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);
}

#if 0
recursive_render(scene, scene->mRootNode, 0.5);
void recursive_render (const struct aiScene *sc, const struct aiNode* nd, float scale)
{
	unsigned int i;
	unsigned int n=0, t;
	aiMatrix4x4 m = nd->mTransformation;

	m.Scaling(aiVector3D(scale, scale, scale), m);

	// update transform
	m.Transpose();
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);


		if(mesh->mNormals == NULL)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}

		if(mesh->mColors[0] != NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}



		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices)
			{
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
			{
				int vertexIndex = face->mIndices[i];	// get group index for current index
				if(mesh->mColors[0] != NULL)
					Color4f(&mesh->mColors[0][vertexIndex]);
				if(mesh->mNormals != NULL)

					if(mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					{
						glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
					}

					glNormal3fv(&mesh->mNormals[vertexIndex].x);
					glVertex3fv(&mesh->mVertices[vertexIndex].x);
			}

			glEnd();

		}

	}


	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n)
	{
		recursive_render(sc, nd->mChildren[n], scale);
	}

	glPopMatrix();
}
#endif
