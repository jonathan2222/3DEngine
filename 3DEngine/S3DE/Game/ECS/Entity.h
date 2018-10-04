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
		Entity(Ecs* ecs);
		~Entity() {}
		void addComponent(ComponentID componentId, BaseComponent* component, std::map<ComponentID, std::vector<Byte>>& memory);
		void deleteComponent(ComponentID componentId, ComponentIndex componentIndex, std::map<ComponentID, std::vector<Byte>>& memory);

		template<typename C>
		C* getComponent();

		EntityID id;

		std::vector<std::pair<ComponentID, ComponentIndex>> components;
		ComponentBitset componentBitset;
		unsigned int flags;

	private:
		Ecs * ecsPtr;
	};
	
	template<typename C>
	inline C* Entity::getComponent()
	{
		ComponentID compId = C::ID;
		ComponentIndex compIndex = 0;
		bool found = false;
		for(auto comp : this->components)
			if (compId == comp.first)
			{
				compIndex = comp.second;
				found = true;
				break;
			}
		if (!found) return nullptr;
		C* comp = (C*)(&this->ecsPtr->componentsMemory[compId][compIndex]);
		return comp;
	}
}

#endif