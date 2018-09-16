#include "Model.h"

s3de::Model::Model(std::vector<Mesh*> meshes)
{
	for (Mesh* m : meshes)
		this->meshes.push_back(m);
}

s3de::Model::Model(std::vector<Mesh*> meshes, std::vector<Material::MaterialData> materials)
{
	for (Mesh* m : meshes)
		this->meshes.push_back(m);
	for(Material::MaterialData m : materials)
		this->materials.push_back(m);
}

s3de::Model::~Model()
{
	for (unsigned int i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];
}

const std::vector<s3de::Mesh*>& s3de::Model::getMeshes() const
{
	return this->meshes;
}

const std::vector<s3de::Material::MaterialData>& s3de::Model::getMaterials() const
{
	return this->materials;
}

bool s3de::Model::hasMaterial() const
{
	return !this->materials.empty();
}
