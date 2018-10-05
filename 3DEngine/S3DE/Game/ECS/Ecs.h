#ifndef S3DE_ECS_H
#define S3DE_ECS_H

#include <vector>
#include <map>

#include "EcsDefines.h"
#include "Component.h"
#include "Entity.h"
#include "System.h"

namespace s3de
{
	class Renderer;
	class Ecs
	{
	friend Entity;
	public:
		Ecs();
		~Ecs();

		template<typename ...Comps>
		Entity* makeEntity(Comps... comps);
		template<typename... C>
		Entity* makeEntity();
		Entity* makeEntity(const std::vector<ECSBaseComponent*>& components, const std::vector<ComponentID>& ids);

		void removeEntity(Entity* entity);

		void initSystems(Renderer & renderer);
		void updateSystems(Renderer & renderer, float dt);

		bool addSystem(ECSISystem* system);
		bool removeSystem(ECSISystem* system);

		bool addRenderSystem(ECSIRenderSystem* system);
		bool removeRenderSystem(ECSIRenderSystem* system);

	private:
		std::map<ComponentID, std::vector<Byte>> componentsMemory;
		std::vector<Entity*> entities;
		std::vector<ECSISystem*> systems;
		std::vector<ECSIRenderSystem*> renSystems;
	};

	template<typename ...Comps>
	inline Entity * Ecs::makeEntity(Comps ...comps)
	{
		std::vector<ComponentID> ids = { Comps::ID... };
		std::vector<ECSBaseComponent*> components = { &comps... };
		Entity* entity = makeEntity(components, ids);
		return entity;
	}

	template<typename... C>
	inline Entity* Ecs::makeEntity()
	{
		std::vector<ComponentID> ids = { C::ID... };
		std::vector<ECSBaseComponent*> components = { new C()... };
		Entity* entity = makeEntity(components, ids);
		for (unsigned int i = 0; i < components.size(); i++)
			delete components[i];
		return entity;
	}
}

#endif