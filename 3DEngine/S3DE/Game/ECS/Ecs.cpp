#include "Ecs.h"

s3de::Ecs::Ecs()
{
}

s3de::Ecs::~Ecs()
{
	for (std::map<ComponentID, std::vector<Byte>>::iterator it = this->componentsMemory.begin(); it != this->componentsMemory.end(); it++)
	{
		unsigned int size = BaseComponent::getSize(it->first);
		FreeComponentFunction freeFunction = BaseComponent::getFreeFunction(it->first);
		for (unsigned int i = 0; i < it->second.size(); i += size)
		{
			freeFunction((BaseComponent*)&it->second[i]);
		}
	}

	unsigned int numEntites = this->entities.size();
	for (unsigned int i = 0; i < numEntites; i++)
		delete this->entities[i];

	BaseComponent::deleteComponentTypes();
}

s3de::Entity* s3de::Ecs::makeEntity(const std::vector<BaseComponent*>& components)
{
	Entity* entity = new Entity();
	entity->id = this->entities.size();

	for (unsigned int i = 0; i < components.size(); i++)
		entity->addComponent(components[i], this->componentsMemory);

	this->entities.push_back(entity);
	return entity;
}

void s3de::Ecs::removeEntity(s3de::Entity* entity)
{
	std::vector<std::pair<ComponentID, ComponentIndex>>& components = entity->components;

	for (unsigned int i = 0; i < components.size(); i++)
		entity->deleteComponent(components[i].first, components[i].second, this->componentsMemory);

	// Delete the entity and replace it with the last (if more than one).
	EntityID id = entity->id;
	delete entity;
	if (id != this->entities.size() - 1)
	{
		this->entities[id] = this->entities[this->entities.size() - 1];
		this->entities[id]->id = id;
	}
	this->entities.pop_back();
}
