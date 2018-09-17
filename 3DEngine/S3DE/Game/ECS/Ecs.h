#ifndef S3DE_ECS_H
#define S3DE_ECS_H

#include <vector>
#include "Component.h"

namespace s3de
{
	class Ecs
	{
	public:
		Ecs();
		~Ecs();

		template<typename ...C>
		bool makeEntity();
		bool makeEntity(std::vector<BaseComponent*> components);
	};
	template<typename ...C>
	inline bool Ecs::makeEntity()
	{
		std::vector<Component*> components = { &C ... };
		return makeEntity(components);
	}
}

#endif