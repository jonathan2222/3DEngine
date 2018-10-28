#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "../Component.h"
#include "../System.h"

#include "SM/Maths.h"
#include "SM/MathsTransform.h"
#include "SM/Quaternion/Quaternion.h"

#include "../../../Input/InputManager.h"
#include "../../../Input/InputConfig.h"

#include <iostream>

namespace s3de
{
	struct CameraComponent : public ECSComponent<CameraComponent>
	{
		sm::Mat4 matrix;
		sm::Mat4 view;
		sm::Mat4 projection;
		sm::Vec3 position;
		sm::Vec3 direction;
		float fov;
		float zNear;
		float zFar;
	};

	class CameraSystem : public ECSSystem<CameraComponent>
	{
	public:
		void init(void* data) override
		{
			this->display = (Display*)data;
			std::cout << "Init CameraSystem " << std::endl;

			this->preMousePos.x - 1.f;
			this->preMousePos.y - 1.f;
		}

		void initEntity(Entity* entity) override
		{
			CameraComponent* cameraComp = entity->getComponent<CameraComponent>();

			sm::MathsTransform::initCamera(cameraComp->view, cameraComp->direction, sm::Vec3(0.0f, 1.0f, 0.0f), cameraComp->position);
			sm::MathsTransform::perspective(cameraComp->projection, cameraComp->fov, this->display->getAspectRatio(), cameraComp->zNear, cameraComp->zFar);
			cameraComp->matrix = cameraComp->projection*cameraComp->view;
		}

		void update(float dt, Entity* entity) override
		{
			/*
			CameraComponent* cameraComp = entity->getComponent<CameraComponent>();
			sm::Vec2 mousePos = InputManager::getMousePosition(display->getWindowPtr());
			mousePos.x /= (float)display->getWidth();
			mousePos.y /= display->getHeight();

			float stepX = (float)display->getWidth() / CAMERA_WIDTH;
			float stepY = display->getAspectRatio();
			float cameraHeight = stepY * CAMERA_WIDTH;

			if (s3de::InputManager::press(display->getWindowPtr(), GLFW_KEY_W))
				setPosition(cameraComp->position + (FPS_CAMERA_SPEED * dt) * cameraComp->direction);
			if (s3de::InputManager::press(display->getWindowPtr(), GLFW_KEY_S))
				setPosition(cameraComp->position - (FPS_CAMERA_SPEED * dt) * cameraComp->direction);
			if (s3de::InputManager::press(display->getWindowPtr(), GLFW_KEY_D))
				setPosition(cameraComp->position + (FPS_CAMERA_SPEED * dt) * getRight());
			if (s3de::InputManager::press(display->getWindowPtr(), GLFW_KEY_A))
				setPosition(cameraComp->position - (FPS_CAMERA_SPEED * dt) * getRight());

			if (s3de::InputManager::toggle(display->getWindowPtr(), GLFW_KEY_C))
			{
				// Mouse position has changed!
				if (this->preMousePos != mousePos)
				{
					sm::Vec3 dir = cameraComp->direction;

					sm::Vec2 deltaPos = sm::Vec2(0.5f, 0.5f) - mousePos;
					dir = sm::MathsTransform::rotate(dir, MOUSE_SENSITIVITY_X * deltaPos.x * stepX * dt, getUp());
					dir = sm::MathsTransform::rotate(dir, MOUSE_SENSITIVITY_Y * deltaPos.y * stepY * dt, getRight());
					lookIn(dir, *cameraComp);
				}
			}

			this->preMousePos = mousePos;*/
		}

	private:
		void lookIn(const sm::Vec3 & direction, CameraComponent& comp)
		{
			sm::MathsTransform::initCamera(comp.view, direction, sm::Vec3(0.0f, 1.0f, 0.0f), comp.position);
		}

		Display* display;
		sm::Vec2 preMousePos;
	};
}

#endif
