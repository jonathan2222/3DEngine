#ifndef S3DE_RENDERER_H
#define S3DE_RENDERER_H

#include "../Objects/Model.h"
#include "../Shaders/Shader.h"
#include "../../OpenGLAbstractions/UniformBuffer.h"
#include "SM/Maths.h"

#include <vector>

namespace s3de
{
	/*
		Can only be one instance of this class or else it wont work!!
	*/
	class Camera;
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

		void setCamera(Camera* camera);
		void setCamera(sm::Mat4* vp, sm::Vec3* pos);
		void applyCamera(Shader* shader = nullptr) const;

		Shader& getShader();

	private:
		Camera* camera;
		sm::Mat4* vp;
		sm::Vec3* camPos;
		Shader* shader;
		UniformBuffer* ubo;
		bool isWireframeOn;
	};
}

#endif
