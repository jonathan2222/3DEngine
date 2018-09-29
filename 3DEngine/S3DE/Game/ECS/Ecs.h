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
		Entity* makeEntity(const std::vector<BaseComponent*>& components);
		void removeEntity(Entity* entity);

		void updateSystems(float dt);

		template<typename T>
		bool addSystem();
		template<typename T>
		bool removeSystem();

	private:
		template<typename T>
		int getSystem();

		std::map<ComponentID, std::vector<Byte>> componentsMemory;
		std::vector<Entity*> entities;
		std::vector<ISystem*> systems;
	};

	template<typename C>
	inline Entity * Ecs::makeEntity(C* c)
	{
		// --------- This will make it work without using getComponent ---------
		C::ID;
		// ---------------------------------------------------------------------
		std::vector<BaseComponent*> components = { c };
		return makeEntity(components);
	}

	template<typename A, typename B>
	inline Entity * Ecs::makeEntity(A * a, B * b)
	{
		// --------- This will make it work without using getComponent ---------
		A::ID;
		B::ID;
		// ---------------------------------------------------------------------
		std::vector<BaseComponent*> components = { a, b };
		return makeEntity(components);
	}

	template<typename A, typename B, typename C>
	inline Entity * Ecs::makeEntity(A * a, B * b, C * c)
	{
		// --------- This will make it work without using getComponent ---------
		A::ID;
		B::ID;
		C::ID;
		// ---------------------------------------------------------------------
		std::vector<BaseComponent*> components = { a, b, c };
		return makeEntity(components);
	}

	template<typename... C>
	inline Entity* Ecs::makeEntity()
	{
		// --------- This will make it work without using getComponent ---------
		std::vector<ComponentID> ids = { C::ID... };
		// ---------------------------------------------------------------------

		std::vector<BaseComponent*> components = { new C()... };
		Entity* entity = makeEntity(components);
		for (unsigned int i = 0; i < components.size(); i++)
			delete components[i];
		return entity;
	}
	template<typename T>
	inline bool Ecs::addSystem()
	{
		int index = getSystem<T>();
		if (index == -1)
		{
			T* sys = new T();
			this->systems.push_back(sys);
			return true;
		}
		return false;
	}
	template<typename T>
	inline bool Ecs::removeSystem()
	{
		int index = getSystem<T>();
		if (index != -1)
		{
			ISystem* temp = this->systems[this->systems.size() - 1];
			delete this->systems[i];
			this->systems[i] = temp;
			this->systems.pop_back();
			return true;
		}
		return false;
	}
	template<typename T>
	inline int Ecs::getSystem()
	{
		for (unsigned int i = 0; i < this->systems.size(); i++)
			if (T::ID == this->systems[i]->getId())
				return i;
		return -1;
	}
}

#endif