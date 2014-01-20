#include <GL/glew.h>
#include "model.h"
#include "common/debug.h"
#include <fstream>
#include <Image.h>


static const GLint internalFormats[] = {
	0,
	// Unsigned formats
	GL_INTENSITY8,
	GL_LUMINANCE8_ALPHA8,
	GL_RGB8,
	GL_RGBA8,

	GL_INTENSITY16,
	GL_LUMINANCE16_ALPHA16,
	GL_RGB16,
	GL_RGBA16,

	// Signed formats
	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0,

	// Float formats
	GL_INTENSITY_FLOAT16_ATI,
	GL_LUMINANCE_ALPHA_FLOAT16_ATI,
	GL_RGB_FLOAT16_ATI,
	GL_RGBA_FLOAT16_ATI,

	GL_INTENSITY_FLOAT32_ATI,
	GL_LUMINANCE_ALPHA_FLOAT32_ATI,
	GL_RGB_FLOAT32_ATI,
	GL_RGBA_FLOAT32_ATI,

	// Signed integer formats
	0, // GL_INTENSITY16I_EXT,
	0, // GL_LUMINANCE_ALPHA16I_EXT,
	0, // GL_RGB16I_EXT,
	0, // GL_RGBA16I_EXT,

	0, // GL_INTENSITY32I_EXT,
	0, // GL_LUMINANCE_ALPHA32I_EXT,
	0, // GL_RGB32I_EXT,
	0, // GL_RGBA32I_EXT,

	// Unsigned integer formats
	0, // GL_INTENSITY16UI_EXT,
	0, // GL_LUMINANCE_ALPHA16UI_EXT,
	0, // GL_RGB16UI_EXT,
	0, // GL_RGBA16UI_EXT,

	0, // GL_INTENSITY32UI_EXT,
	0, // GL_LUMINANCE_ALPHA32UI_EXT,
	0, // GL_RGB32UI_EXT,
	0, // GL_RGBA32UI_EXT,

	// Packed formats
	0, // RGBE8 not directly supported
	0, // GL_RGB9_E5,
	0, // GL_R11F_G11F_B10F,
	GL_RGB5,
	GL_RGBA4,
	GL_RGB10_A2,

	// Depth formats
	GL_DEPTH_COMPONENT16,
	GL_DEPTH_COMPONENT24,
	GL_DEPTH24_STENCIL8_EXT,
	0, // GL_DEPTH_COMPONENT32F,

	// Compressed formats
	GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
	GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
	GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
	0, // ATI1N not yet supported
	GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI,
};

static const GLenum srcFormats[] = { 0, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA };

static const GLenum srcTypes[] = {
	0,
	// Unsigned formats
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_BYTE,

	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_SHORT,

	// Signed formats
	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0,

	// Float formats
	0,//GL_HALF_FLOAT_ARB,
	0,//GL_HALF_FLOAT_ARB,
	0,//GL_HALF_FLOAT_ARB,
	0,//GL_HALF_FLOAT_ARB,

	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,

	// Signed integer formats
	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0,

	// Unsigned integer formats
	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0,

	// Packed formats
	0, // RGBE8 not directly supported
	0, // RGBE9E5 not supported
	0, // RG11B10F not supported
	GL_UNSIGNED_SHORT_5_6_5,
	GL_UNSIGNED_SHORT_4_4_4_4_REV,
	GL_UNSIGNED_INT_2_10_10_10_REV,

	// Depth formats
	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_INT,
	GL_UNSIGNED_INT_24_8_EXT,
	0, // D32F not supported

	// Compressed formats
	0,
	0,
	0,
	0,
	0,
};

void Material::BindForLoadStore(GLenum access)
{
	glBindImageTexture(0, mTexID, 0, GL_FALSE, 0, access, mTexFormat);
}

void Material::SetDiffuseTexture(const char* path)
{
    Image img;
    GLenum eTarget = GL_TEXTURE_2D;

    glGenTextures(1, &mTexID);
    glBindTexture(eTarget, mTexID);

    img.loadImage(path);

    FORMAT format = img.getFormat();
    GLenum srcFormat = srcFormats[getChannelCount(format)];
    GLenum srcType = srcTypes[format];
    GLint internalFormat = internalFormats[format];
	mTexFormat = internalFormat;

	// Upload it all
	uint8_t *src;
	int mipMapLevel = 0;
	while ((src = img.getPixels(mipMapLevel)) != NULL){
		if (img.isCube()){
			int size = img.getMipMappedSize(mipMapLevel, 1) / 6;
			for (uint32_t i = 0; i < 6; i++){
				if (isCompressedFormat(format)){
					glCompressedTexImage2DARB(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), img.getHeight(mipMapLevel), 0, size, src + i * size);
				} else {
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), img.getHeight(mipMapLevel), 0, srcFormat, srcType, src + i * size);
				}
			}
		} else if (img.is3D()){
			if (isCompressedFormat(format)){
				glCompressedTexImage3DARB(eTarget, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), img.getHeight(mipMapLevel), img.getDepth(mipMapLevel), 0, img.getMipMappedSize(mipMapLevel, 1), src);
			} else {
				glTexImage3D(eTarget, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), img.getHeight(mipMapLevel), img.getDepth(mipMapLevel), 0, srcFormat, srcType, src);
			}
		} else if (img.is2D()){
			if (isCompressedFormat(format)){
				glCompressedTexImage2DARB(eTarget, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), img.getHeight(mipMapLevel), 0, img.getMipMappedSize(mipMapLevel, 1), src);
			} else {
				glTexImage2D(eTarget, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), img.getHeight(mipMapLevel), 0, srcFormat, srcType, src);
			}
		} else {
			glTexImage1D(eTarget, mipMapLevel, internalFormat, img.getWidth(mipMapLevel), 0, srcFormat, srcType, src);
		}
		mipMapLevel++;
	}
}
void Material::Apply()
{
    glBindTexture(GL_TEXTURE_2D, mTexID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

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
		DebugString( importer.GetErrorString());
		return false;
	}

	mScene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if( !mScene)
	{
		DebugString( importer.GetErrorString());
		return false;
	}

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

	CreateBuffers();
    CreateMaterial();

	return true;
}

void Model::CreateMaterial()
{
    const struct aiMesh* mesh = mScene->mMeshes[0];
    const aiMaterial *mtl = mScene->mMaterials[mesh->mMaterialIndex];

    aiString texPath;	//contains filename of texture

    if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath))
    {
        //Textures for models currently reside in ./models
        std::string fullPath ("models/");
        fullPath += texPath.C_Str();
        mMaterial.SetDiffuseTexture(fullPath.c_str());
    }
}

void Model::CreateBuffers()
{
	const struct aiMesh* mesh = mScene->mMeshes[0];

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
			*verticesPtr++ = 1.0f - mesh->mTextureCoords[0][vtx].y;
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

void Model::RecursiveDraw(ITransform& world, const  aiNode* nd)
{
	Vectormath::Aos::Matrix4 localWorld = world.GetWorldMatrix();

    Vectormath::Aos::Matrix4 originalWorld = localWorld;

	aiMatrix4x4 m = nd->mTransformation;

	m.Transpose();

    localWorld *= Vectormath::Aos::Matrix4(
        Vectormath::Aos::Vector4(m.a1, m.a2, m.a3, m.a4),
        Vectormath::Aos::Vector4(m.b1, m.b2, m.b3, m.b4),
        Vectormath::Aos::Vector4(m.c1, m.c2, m.c3, m.c4),
        Vectormath::Aos::Vector4(m.d1, m.d2, m.d3, m.d4));

	for(int n =0; n < nd->mNumMeshes; ++n)
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
	
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mVertexSize, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mVertexSize, (void*)(sizeof(float)*3));
		if(mHaveTexCoords)
		{
            glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mVertexSize, (void*)(sizeof(float)*6));
		}

		world.SetWorldMatrix(localWorld);

		glDrawElements(GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);
	}

	// draw all children
	for (int n = 0; n < nd->mNumChildren; ++n) {
		RecursiveDraw(world, nd->mChildren[n]);
	}

    world.SetWorldMatrix(originalWorld);
}

void Model::Draw(ITransform& world)
{
	glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuf);

    mMaterial.Apply();

	RecursiveDraw(world, mScene->mRootNode);
}

