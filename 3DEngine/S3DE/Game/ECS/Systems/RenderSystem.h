#ifndef S3DE_RENDER_SYSTEM_H
#define S3DE_RENDER_SYSTEM_H

#include <iostream>

#include "../Component.h"
#include "../System.h"
#include "../Components/TransformComponent.h"

#include "../../../Graphics/Rendering/Renderer.h"
#include "../../../Graphics/Shaders/Shader.h"
#include "../../../Graphics/Objects/Model.h"

#include "../../../Scene/Camera/FPSCamera.h"
#include "../../../Input/InputManager.h"

#include "SM\Vectors\Vec3.h"
#include "../../../Graphics/GUI/WindowConfig.h"

namespace s3de
{
	struct RenderableComponent : ECSComponent<RenderableComponent>
	{
		bool visible = true;
		s3de::Model* model;
	};

	class RenderSystem : public ECSRenderSystem<RenderableComponent, TransformComponent>
	{
	public:
		void initRender(Renderer& renderer) override
		{
			std::cout << "Init RenderSystem " << std::endl;
			renderer.resetMaterial(); // Use default material
			this->shader = &renderer.getShader();
			this->camera.create(sm::Vec3(0.0f, 0.0f, -1.0f), sm::Vec3(0.0f, 0.0f, 5.0f), (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT);
		}

		void init(Entity* entity) override
		{
		}

		void render(Renderer& renderer, Entity* entity) override
		{
			RenderableComponent* renderableComp = entity->getComponent<RenderableComponent>();
			TransformComponent* transformComp = entity->getComponent<TransformComponent>();

			if (renderableComp->visible)
			{
				sm::Mat4 matrix = transformComp->world * transformComp->model;

				this->shader->bind();
				this->shader->setUniform3fv("camPos", 1, &(this->camera.getPosition())[0]);
				this->shader->setUniformMatrix4fv("matrix", 1, false, &(matrix)[0][0]);
				this->shader->setUniformMatrix4fv("vp", 1, false, &(this->camera.getVP())[0][0]);
				renderer.render(renderableComp->model);
			}
		}

	private:
		s3de::Shader* shader;

		s3de::FPSCamera camera;
	};
}

#endif