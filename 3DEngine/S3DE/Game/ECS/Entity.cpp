#include "Entity.h"
#include "../../Utils/BitManipulation.h"
#include "Ecs.h"

s3de::Entity::Entity(Ecs * ecs)
{
	this->componentBitset = 0; 
	this->ecsPtr = ecs;
	this->flags = 0;
}

void s3de::Entity::addComponent(ComponentID componentId, ECSBaseComponent * component, std::map<ComponentID, std::vector<Byte>>& memory)
{
	// Allocate and copy data to memory.
	CreateComponentFunction createfunction = component->getCreateFunction(componentId);
	ComponentIndex compIndex = createfunction(memory[componentId], this, component);
	// Store index to component.
	this->components.push_back(std::pair<ComponentID, ComponentIndex>(componentId, compIndex));
	Utils::setBit<ComponentBitset>(this->componentBitset, componentId);
}

void s3de::Entity::deleteComponent(ComponentID componentId, ComponentIndex componentIndex, std::map<ComponentID, std::vector<Byte>>& memory)
{
	unsigned int typeSize = ECSBaseComponent::getSize(componentId);
	ComponentIndex lastIndex = memory[componentId].size() - typeSize;

	FreeComponentFunction freeFunction = ECSBaseComponent::getFreeFunction(componentId);
	ECSBaseComponent* component = (ECSBaseComponent*)&memory[componentId][componentIndex];
	ECSBaseComponent* movedComponent = (ECSBaseComponent*)&memory[componentId][lastIndex];
	freeFunction(component);

	if (componentIndex == lastIndex)
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
			lastComponenets[i].second = componentIndex;
			break;
		}
	}

	memory[componentId].resize(lastIndex);

	Utils::clearBit<ComponentBitset>(this->componentBitset, componentId);
}
