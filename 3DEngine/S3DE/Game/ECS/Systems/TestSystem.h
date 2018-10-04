#ifndef S3DE_TEST_SYSTEM_H
#define S3DE_TEST_SYSTEM_H

#include "../System.h"
#include "../Components/BoolComponent.h"
#include "../Components/PositionComponent.h"

namespace s3de
{
	class TestSystem : public System<PositionComponent, BoolComponent>
	{
	public:
		TestSystem();
		~TestSystem();

		void init() override
		{

		}

		void update(float dt, Entity* entity) override
		{

		}

	private:
	};
}

#endif
