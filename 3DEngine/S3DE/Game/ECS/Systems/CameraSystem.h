#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "../Component.h"
#include "../System.h"

#include "SM/Maths.h"
#include "SM/MathsTransform.h"
#include "SM/Quaternion/Quaternion.h"

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
			//CameraComponent* cameraComp = entity->getComponent<CameraComponent>();

		}

	private:
		Display* display;
	};
}

#endif
