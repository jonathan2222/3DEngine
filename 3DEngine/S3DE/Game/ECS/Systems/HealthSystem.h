#ifndef S3DE_HEALTH_SYSTEM_H
#define S3DE_HEALTH_SYSTEM_H

#include "../System.h"
#include "../Component.h"
#include <iostream>
#include <random>

namespace s3de
{
	struct HealthComponent : public Component<HealthComponent>
	{
		float health;
	};

	class HealthSystem : public System<HealthComponent>
	{
	public:
		void init(Entity* entity) override
		{
			HealthComponent* comp = entity->getComponent<HealthComponent>();
			comp->health = rand() % 11 + 20;
			internalTime = 0.0f;
			std::cout << "Init HealthSystem, Health: " << comp->health << std::endl;
		}

		void update(float dt, Entity* entity) override
		{
			HealthComponent* comp = entity->getComponent<HealthComponent>();
			comp->health -= 0.1f;

			if (comp->health <= 0.0f)
			{
				printf("[HealthSystem] Entity[%d] DEATH HAS FALLEN UPON IT! [dt: %f]\n", entity->id, comp->health, dt);
				entity->flags |= ENTITY_REMOVE;
			}
			else
			{
				internalTime += dt;
				if (internalTime > 1.0f)
				{
					printf("[HealthSystem] Entity[%d] has %f utits of health left. [dt: %f]\n", entity->id, comp->health, dt);
					internalTime = 0.0f;
				}
			}
		}

	private:
		float internalTime = 0.0f;
	};
}

#endif