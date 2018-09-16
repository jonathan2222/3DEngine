#ifndef S3DE_RENDERER_H
#define S3DE_RENDERER_H

#include "../Objects/Model.h"
#include "../Shaders/Shader.h"
#include "../../OpenGLAbstractions/UniformBuffer.h"

#include <vector>

namespace s3de
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void setWireframe(bool on);

		void render(const Model* model);
		void render(const Model* model, const Material::MaterialData& material);
		void render(const std::vector<Mesh*>& meshes, const Material::MaterialData& material) const;
		void render(const std::vector<Mesh*>& meshes, const std::vector<Material::MaterialData>& materials) const;

		void resetMaterial();

		Shader& getShader();

	private:
		Shader* shader;
		UniformBuffer* ubo;
		bool isWireframeOn;
	};
}

#endif
