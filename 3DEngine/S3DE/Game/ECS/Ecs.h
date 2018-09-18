#ifndef S3DE_ECS_H
#define S3DE_ECS_H

#include <vector>
#include <map>

#include"EcsDefines.h"
#include "Component.h"

namespace s3de
{
	class Ecs
	{
	public:
		Ecs();
		~Ecs();

		template<typename ...C>
		EntityHandle makeEntity();
		EntityHandle makeEntity(const std::vector<BaseComponent*>& components);
		void removeEntity(EntityHandle handle);

	private:
		struct Entity
		{
			Ecs* ecs;
			std::vector<std::pair<ComponentID, ComponentIndex>> components;
			Entity() {}
			void addComponent(BaseComponent* component)
			{
				const ComponentID id = components.size();
				// Allocate and copy data to memory.
				CreateComponentFunction createfunction = component->getCreateFunction(id);
				ComponentIndex compIndex = createfunction(ecs->componentsMemory[id], this, component);
				// Store index to component.
				this->components.push_back(std::pair<ComponentID, ComponentIndex>(id, compIndex));
			}
			void deleteComponent(EntityID entityId, ComponentID componentId, ComponentIndex componentIndex);
		};

		std::map<ComponentID, std::vector<Byte>> componentsMemory;
		std::vector<std::pair<EntityID, Entity>> entities;
	};
	template<typename ...C>
	inline EntityHandle Ecs::makeEntity()
	{
		std::vector<Component*> components = { &C ... };
		return makeEntity(components);
	}
}

#endif