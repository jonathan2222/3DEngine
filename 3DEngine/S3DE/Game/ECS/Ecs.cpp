#include "Ecs.h"

s3de::Ecs::Ecs()
{
}

s3de::Ecs::~Ecs()
{
}

EntityHandle s3de::Ecs::makeEntity(const std::vector<BaseComponent*>& components)
{
	std::pair<EntityID, Entity> data;
	data.first = this->entities.size();
	data.second.ecs = this;

	for (unsigned int i = 0; i < components.size(); i++)
		data.second.addComponent(components[i]);

	this->entities.push_back(data);
	return &this->entities[data.first].second;
}

void s3de::Ecs::removeEntity(EntityHandle handle)
{
	Entity* entity = (Entity*)handle;
	std::vector<std::pair<ComponentID, ComponentIndex>>& components = entity->components;

	for (unsigned int i = 0; i < components.size(); i++)
	{
		entity->deleteComponent(i, components[i].first, components[i].second);
	}

	// TOOD: remove entity.
}

void s3de::Ecs::Entity::deleteComponent(EntityID entityId, ComponentID componentId, ComponentIndex componentIndex)
{
	std::vector<Byte>& memory = this->ecs->componentsMemory[componentId];
	unsigned int typeSize = BaseComponent::getSize(componentId);
	ComponentIndex compIndex = components[entityId].second;
	ComponentIndex lastIndex = components.size() - typeSize;

	FreeComponentFunction freeFunction = BaseComponent::getFreeFunction(componentId);
	BaseComponent* component = (BaseComponent*)&memory[compIndex];
	BaseComponent* lastComponent = (BaseComponent*)&memory[lastIndex];
	freeFunction(component);

	if (compIndex == lastIndex)
	{
		memory.resize(lastIndex);
		return;
	}

	std::memcpy(component, lastComponent, typeSize);
	std::vector<std::pair<ComponentID, ComponentIndex>>& lastComponenets = ((Entity*)lastComponent->entityHandle)->components;
	for (unsigned int i = 0; i < lastComponenets.size(); i++)
	{
		if (lastComponenets[i].first == componentId && lastComponenets[i].second == lastIndex)
		{
			lastComponenets[i].second = compIndex;
			break;
		}
	}
}
