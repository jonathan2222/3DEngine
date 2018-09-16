#include "ModelLoader.h"

#include <ASSIMP\Importer.hpp>
#include <ASSIMP\scene.h>
#include <ASSIMP\postprocess.h>

#include "../Graphics/Objects/Material.h"
#include "SM/Vectors/Vec4.h"

s3de::ModelLoader::ModelLoader()
{
}

s3de::ModelLoader::~ModelLoader()
{
}

s3de::Model* s3de::ModelLoader::loadModel(const std::string & pathName)
{
	Assimp::Importer importer;
	const aiScene* model = importer.ReadFile(pathName, aiProcessPreset_TargetRealtime_Fast);

	std::vector<Material::MaterialData> materials;

	std::vector<s3de::Mesh*> meshes;
	if (model->mNumMeshes > 0)
	{
		for (unsigned int i = 0; i < model->mNumMeshes; i++)
		{
			aiMesh* mesh = model->mMeshes[i];
			std::vector<s3de::Vertex> vertices;
			vertices.reserve(mesh->mNumVertices);

			aiMaterial* material = model->mMaterials[mesh->mMaterialIndex];
			aiColor4D ambientColor;
			aiColor4D diffuseColor;
			aiColor4D specularColor;
			float shininess;
			aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
			aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
			Material::MaterialData finalMaterial;
			finalMaterial.ambientColor = sm::Vec4(ambientColor.r, ambientColor.g, ambientColor.b, 1.0);
			finalMaterial.diffuseColor = sm::Vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, 1.0);
			finalMaterial.specularColor = sm::Vec4(specularColor.r, specularColor.g, specularColor.b, shininess);
			materials.push_back(finalMaterial);

			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				aiVector3D pos = mesh->mVertices[j];
				aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[j] : aiVector3D(0.0f, 0.0f, 0.0f);
				aiVector3D uv = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][j] : aiVector3D(0.0f, 0.0f, 0.0f);
				vertices.push_back({ { pos.x, pos.y, pos.z },{ normal.x, normal.y, normal.z } });
			}

			std::vector<unsigned int> indices;
			indices.reserve(mesh->mNumFaces * 3);
			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				// This should only be 3 vertices because the preprocess should triangulate the faces.
				indices.push_back(mesh->mFaces[j].mIndices[0]);
				indices.push_back(mesh->mFaces[j].mIndices[1]);
				indices.push_back(mesh->mFaces[j].mIndices[2]);
			}

			meshes.push_back(new s3de::Mesh(vertices, indices));
		}
	}

	return new Model(meshes, materials);
}
