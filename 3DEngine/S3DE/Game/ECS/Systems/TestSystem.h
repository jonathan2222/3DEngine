#ifndef S3DE_TEST_SYSTEM_H
#define S3DE_TEST_SYSTEM_H

#include "../System.h"
#include "../Components/BoolComponent.h"
#include "../Components/PositionComponent.h"
#include <iostream>

namespace s3de
{
	class TestSystem : public ECSSystem<PositionComponent, BoolComponent>
	{
	public:
		TestSystem();
		~TestSystem();

		void init() override
		{
			std::cout << "Init TestStstem" << std::endl;
		}

		void initEntity(Entity* entity) override
		{
			
		}

		void update(float dt, Entity* entity) override
		{
			//std::cout << "Update TestStstem with entity " << entity->id << std::endl;
		}

	private:
	};
}

#endif
