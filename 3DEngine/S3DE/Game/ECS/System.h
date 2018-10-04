#ifndef S3DE_SYSTEM_H
#define S3DE_SYSTEM_H

#include <vector>

#include "Component.h"
#include "Entity.h"
#include "EcsDefines.h"
#include "../../Utils/BitManipulation.h"

namespace s3de
{
	
	class ISystem
	{
	public:
		virtual void init(Entity* entity) = 0;
		virtual void update(float dt, Entity* entity) = 0;
		
		ComponentBitset getComponentBitset() const
		{
			return this->componentBitset;
		}

		bool hasComponents(ComponentBitset componentBitset) const
		{
			return this->componentBitset == componentBitset;
		}

		const std::vector<ComponentID>& getRequirements() const
		{
			return this->requirements;
		}

		void setEcsPtr(Ecs* ecs)
		{
			this->ecsPtr = ecs;
		}

	protected:
		Ecs * ecsPtr;
		std::vector<ComponentID> requirements;
		ComponentBitset componentBitset;
	};

	template<typename... Requirements>
	class System : public ISystem
	{
	public:
		System();
	};

	template<typename ...Requirements>
	inline System<Requirements...>::System()
	{
		this->requirements = { Requirements::ID... };
		this->componentBitset = 0;
		for (ComponentID id : this->requirements)
			Utils::setBit<ComponentBitset>(this->componentBitset, id);
	}
}

#endif
