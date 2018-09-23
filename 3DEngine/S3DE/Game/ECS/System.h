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
		virtual void init() = 0;
		virtual void update(float dt, Entity* entity) = 0;

		unsigned int ID;
	private:
		std::vector<ComponentID> requirements;
	};

	template<typename... Requirements>
	class System : public ISystem
	{
	public:
		System();
	};

	template<typename... Requirements>
	inline System<Requirements...>::System()
	{
		this->requirements = { Requirements::ID... }
	}
}

#endif
