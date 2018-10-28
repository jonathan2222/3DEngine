#ifndef S3DE_MODEL_H
#define S3DE_MODEL_H

#include "Mesh.h"
#include "Material.h"
#include <vector>

namespace s3de
{
	class Model
	{
	public:
		Model(std::vector<Mesh*> meshes);
		Model(std::vector<Mesh*> meshes, std::vector<Material::MaterialData> materials);
		~Model();

		const std::vector<Mesh*>& getMeshes() const;
		std::vector<Material::MaterialData>& getMaterials();

		bool hasMaterial() const;

	private:
		std::vector<Mesh*> meshes;
		std::vector<Material::MaterialData> materials;
	};
}

#endif
