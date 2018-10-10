#include "Ecs.h"
#include "../../Utils/BitManipulation.h"

s3de::Ecs::Ecs()
{
}

s3de::Ecs::~Ecs()
{
	for (std::map<ComponentID, std::vector<Byte>>::iterator it = this->componentsMemory.begin(); it != this->componentsMemory.end(); it++)
	{
		unsigned int size = ECSBaseComponent::getSize(it->first);
		FreeComponentFunction freeFunction = ECSBaseComponent::getFreeFunction(it->first);
		for (unsigned int i = 0; i < it->second.size(); i += size)
		{
			freeFunction((ECSBaseComponent*)&it->second[i]);
		}
	}

	unsigned int numEntites = this->entities.size();
	for (unsigned int i = 0; i < numEntites; i++)
		delete this->entities[i];

	for (unsigned int i = 0; i < this->systems.size(); i++)
		delete this->systems[i].first;

	for (unsigned int i = 0; i < this->renSystems.size(); i++)
		delete this->renSystems[i];

	ECSBaseComponent::deleteComponentTypes();
}

s3de::Entity* s3de::Ecs::makeEntity(const std::vector<ECSBaseComponent*>& components, const std::vector<ComponentID>& ids)
{
	Entity* entity = new Entity(this);
	entity->id = this->entities.size();

	for (unsigned int i = 0; i < components.size(); i++)
		entity->addComponent(ids[i], components[i], this->componentsMemory);

	this->entities.push_back(entity);
	return entity;
}

void s3de::Ecs::removeEntity(s3de::Entity* entity)
{
	std::vector<std::pair<ComponentID, ComponentIndex>>& components = entity->components;

	for (unsigned int i = 0; i < components.size(); i++)
		entity->deleteComponent(components[i].first, components[i].second, this->componentsMemory);

	EntityID id = entity->id;

	// Delete the entity and replace it with the last (if more than one).
	delete entity;
	this->entities[id] = this->entities[this->entities.size() - 1];
	this->entities[id]->id = id;
	this->entities.pop_back();
}

void s3de::Ecs::initSystems(Renderer & renderer)
{
	for (unsigned int j = 0; j < this->systems.size(); j++)
		this->systems[j].first->init(this->systems[j].second);

	for (unsigned int j = 0; j < this->renSystems.size(); j++)
		this->renSystems[j]->initRender(renderer);

	for (unsigned int i = 0; i < this->entities.size(); i++)
	{
		for (unsigned int j = 0; j < this->systems.size(); j++)
			if (this->systems[j].first->hasComponents(this->entities[i]->componentBitset))
				this->systems[j].first->initEntity(this->entities[i]);

		for (unsigned int j = 0; j < this->renSystems.size(); j++)
			if (this->renSystems[j]->hasComponents(this->entities[i]->componentBitset))
				this->renSystems[j]->initEntity(this->entities[i]);
	}
}

void s3de::Ecs::updateSystems(Renderer & renderer, float dt)
{
	std::vector<Entity*> entitiesToRemove;
	for (unsigned int i = 0; i < this->entities.size(); i++)
	{
		bool removeFlagHasSet = false;
		for (unsigned int j = 0; j < this->systems.size(); j++)
		{
			if (this->systems[j].first->hasComponents(this->entities[i]->componentBitset))
				this->systems[j].first->update(dt, this->entities[i]);

			if (!removeFlagHasSet && Utils::isBitSet<unsigned int>(this->entities[i]->flags, ENTITY_REMOVE_BIT))
			{
				entitiesToRemove.push_back(this->entities[i]);
				removeFlagHasSet = true;
			}
		}

		for (unsigned int j = 0; j < this->renSystems.size(); j++)
			if (this->renSystems[j]->hasComponents(this->entities[i]->componentBitset))
				this->renSystems[j]->render(renderer, this->entities[i]);
	}

	for (unsigned int i = 0; i < entitiesToRemove.size(); i++)
		removeEntity(entitiesToRemove[i]);
}

bool s3de::Ecs::addSystem(ECSISystem * system, void* data)
{
	system->setEcsPtr(this);
	this->systems.push_back(std::pair<ECSISystem*, void*>(system, data));
	return true;
}

bool s3de::Ecs::removeSystem(ECSISystem * system)
{
	for(unsigned int i = 0; i < this->systems.size(); i++)
		if (this->systems[i].first == system)
		{
			delete this->systems[i].first;
			this->systems[i] = this->systems[this->systems.size() - 1];
			this->systems.pop_back();
			return true;
		}
	return false;
}

bool s3de::Ecs::addRenderSystem(ECSIRenderSystem * system)
{
	system->setEcsPtr(this);
	this->renSystems.push_back(system);
	return true;
}

bool s3de::Ecs::removeRenderSystem(ECSIRenderSystem * system)
{
	for (unsigned int i = 0; i < this->renSystems.size(); i++)
		if (this->renSystems[i] == system)
		{
			delete this->renSystems[i];
			this->renSystems[i] = this->renSystems[this->renSystems.size() - 1];
			this->renSystems.pop_back();
			return true;
		}
	return false;
}
