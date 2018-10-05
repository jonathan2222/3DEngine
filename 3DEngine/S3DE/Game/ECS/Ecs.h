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
	class Ecs
	{
	friend Entity;
	public:
		Ecs();
		~Ecs();

		template<typename C>
		Entity* makeEntity(C* c);
		template<typename A, typename B>
		Entity* makeEntity(A* a, B* b);
		template<typename A, typename B, typename C>
		Entity* makeEntity(A* a, B* b, C* c);

		template<typename... C>
		Entity* makeEntity();
		Entity* makeEntity(const std::vector<BaseComponent*>& components, const std::vector<ComponentID>& ids);
		// Does not check if entity was found! Only returns false if not all components were deleted.
		void removeEntity(Entity* entity);

		void initSystems();
		void updateSystems(float dt);

		bool addSystem(ISystem* system);
		bool removeSystem(ISystem* system);

	private:
		std::map<ComponentID, std::vector<Byte>> componentsMemory;
		std::vector<Entity*> entities;
		std::vector<ISystem*> systems;
	};

	template<typename A>
	inline Entity * Ecs::makeEntity(A* c)
	{
		std::vector<BaseComponent*> components = { c };
		std::vector<ComponentID> ids = { A::ID };
		return makeEntity(components, ids);
	}

	template<typename A, typename B>
	inline Entity * Ecs::makeEntity(A * a, B * b)
	{
		std::vector<BaseComponent*> components = { a, b };
		std::vector<ComponentID> ids = { A::ID, B::ID };
		return makeEntity(components, ids);
	}

	template<typename A, typename B, typename C>
	inline Entity * Ecs::makeEntity(A * a, B * b, C * c)
	{
		std::vector<BaseComponent*> components = { a, b, c };
		std::vector<ComponentID> ids = { A::ID, B::ID, C::ID };
		return makeEntity(components, ids);
	}

	template<typename... C>
	inline Entity* Ecs::makeEntity()
	{
		std::vector<ComponentID> ids = { C::ID... };

		std::vector<BaseComponent*> components = { new C()... };
		Entity* entity = makeEntity(components, ids);
		for (unsigned int i = 0; i < components.size(); i++)
			delete components[i];
		return entity;
	}
}

#endif