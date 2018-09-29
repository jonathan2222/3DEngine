#ifndef S3DE_SYSTEM_H
#define S3DE_SYSTEM_H

#include <vector>

#include "Component.h"
#include "Entity.h"
#include "EcsDefines.h"

namespace s3de
{
	class ISystem
	{
	public:
		static unsigned int registerSystem();

		virtual void init() = 0;
		virtual void update(float dt, Entity* entity) = 0;

		unsigned int getId() const
		{
			return id;
		}

	private:
		unsigned int id;
		static unsigned int counter;
		std::vector<ComponentID> requirements;
	};

	template<typename... T>
	struct BSystem : public ISystem
	{
		BSystem();
		static unsigned int ID;
	};

	template<typename ...T>
	inline BSystem<T...>::BSystem() : ISystem()
	{
		this->id = ID;
	}

	template<typename ...T>
	unsigned int BSystem<T...>::ID(registerSystem());

	template<typename... Requirements>
	class System : public BSystem<Requirements...>
	{
	public:
		System();
	};

	template<typename... Requirements>
	inline System<Requirements...>::System() : BSystem<Requirements...>()
	{
		this->requirements = { Requirements::ID... };
	}
}

#endif
