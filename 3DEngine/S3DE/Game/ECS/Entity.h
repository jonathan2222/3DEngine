#ifndef S3DE_ENTITY_H
#define S3DE_ENTITY_H

#include <vector>
#include <map>

#include "Component.h"
#include "EcsDefines.h"

namespace s3de
{
	class Ecs;
	struct Entity
	{
		Entity() {}
		void addComponent(BaseComponent* component, std::map<ComponentID, std::vector<Byte>>& memory);
		void deleteComponent(ComponentID componentId, ComponentIndex componentIndex, std::map<ComponentID, std::vector<Byte>>& memory);

		template<typename C>
		C* getComponent(Ecs* ecs);

		EntityID id;

		std::vector<std::pair<ComponentID, ComponentIndex>> components;
	};
	
	template<typename C>
	inline C* Entity::getComponent(Ecs* ecs)
	{
		ComponentID compId = C::ID;
		ComponentIndex compIndex = this->components[compId].second;
		C* comp = (C*)(&ecs->componentsMemory[compId][compIndex]);
		return comp;
	}
}

#endif