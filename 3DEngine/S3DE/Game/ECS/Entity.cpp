#include "Entity.h"

void s3de::Entity::addComponent(BaseComponent * component, std::map<ComponentID, std::vector<Byte>>& memory)
{
	const ComponentID id = components.size();
	// Allocate and copy data to memory.
	CreateComponentFunction createfunction = component->getCreateFunction(id);
	ComponentIndex compIndex = createfunction(memory[id], this, component);
	// Store index to component.
	this->components.push_back(std::pair<ComponentID, ComponentIndex>(id, compIndex));
}

void s3de::Entity::deleteComponent(ComponentID componentId, ComponentIndex componentIndex, std::map<ComponentID, std::vector<Byte>>& memory)
{
	unsigned int typeSize = BaseComponent::getSize(componentId);
	ComponentIndex compIndex = components[componentId].second;
	ComponentIndex lastIndex = memory[componentId].size() - typeSize;

	FreeComponentFunction freeFunction = BaseComponent::getFreeFunction(componentId);
	BaseComponent* component = (BaseComponent*)&memory[componentId][compIndex];
	BaseComponent* movedComponent = (BaseComponent*)&memory[componentId][lastIndex];
	freeFunction(component);

	if (compIndex == lastIndex)
	{
		memory[componentId].resize(lastIndex);
		return;
	}

	std::memcpy(component, movedComponent, typeSize);
	std::vector<std::pair<ComponentID, ComponentIndex>>& lastComponenets = movedComponent->entity->components;
	for (unsigned int i = 0; i < lastComponenets.size(); i++)
	{
		if (lastComponenets[i].first == componentId && lastComponenets[i].second == lastIndex)
		{
			lastComponenets[i].second = compIndex;
			break;
		}
	}

	memory[componentId].resize(lastIndex);
}
