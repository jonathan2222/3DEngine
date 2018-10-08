#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "../Component.h"
#include "../System.h"

#include "SM/Maths.h"
#include "SM/Quaternion/Quaternion.h"

#include <iostream>

namespace s3de
{
	struct CameraComponent : public ECSComponent<CameraComponent>
	{
		sm::Quaternion rotation;
		sm::Vec3 position;
	};

	class CameraSystem : public ECSSystem<CameraComponent>
	{
	public:
		void init() override
		{
			std::cout << "Init CameraSystem " << std::endl;
			
			//this->camera.create(sm::Vec3(0.0f, 0.0f, -1.0f), sm::Vec3(0.0f, 0.0f, 5.0f), (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT);
		}

		void initEntity(Entity* entity) override
		{
			CameraComponent* cameraComp = entity->getComponent<CameraComponent>();
			cameraComp->rotation.setRotation(sm::Vec3(0.0f, 0.0f, -1.0f));
		}

		void update(float dt, Entity* entity) override
		{
			CameraComponent* cameraComp = entity->getComponent<CameraComponent>();

		}

	private:
	};
}

#endif
