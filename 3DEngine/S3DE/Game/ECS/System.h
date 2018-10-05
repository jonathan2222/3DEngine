#ifndef S3DE_SYSTEM_H
#define S3DE_SYSTEM_H

#include <vector>

#include "Component.h"
#include "Entity.h"
#include "EcsDefines.h"
#include "../../Utils/BitManipulation.h"

namespace s3de
{
	
	class ECSISystem
	{
	public:
		ECSISystem() {}
		virtual ~ECSISystem() {}

		virtual void init(Entity* entity) = 0;
		virtual void update(float dt, Entity* entity) = 0;
		
		ComponentBitset getComponentBitset() const
		{
			return this->componentBitset;
		}

		bool hasComponents(ComponentBitset componentBitset) const
		{
			ComponentBitset bitset = this->componentBitset & componentBitset;
			return this->componentBitset == bitset;
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
	class ECSSystem : public ECSISystem
	{
	public:
		ECSSystem();
		virtual ~ECSSystem() {}
	};

	template<typename ...Requirements>
	inline ECSSystem<Requirements...>::ECSSystem()
	{
		this->requirements = { Requirements::ID... };
		this->componentBitset = 0;
		for (ComponentID id : this->requirements)
			Utils::setBit<ComponentBitset>(this->componentBitset, id);
	}

	// ---------------------------------- RENDER SYSTEM ----------------------------------

	class Renderer;
	class ECSIRenderSystem
	{
	public:
		ECSIRenderSystem() {};
		virtual ~ECSIRenderSystem() {}

		virtual void initRender(Renderer& renderer) = 0;
		virtual void init(Entity* entity) = 0;
		virtual void render(Renderer& renderer, Entity* entity) = 0;

		ComponentBitset getComponentBitset() const
		{
			return this->componentBitset;
		}

		bool hasComponents(ComponentBitset componentBitset) const
		{
			ComponentBitset bitset = this->componentBitset & componentBitset;
			return this->componentBitset == bitset;
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
	class ECSRenderSystem : public ECSIRenderSystem
	{
	public:
		ECSRenderSystem();
		virtual ~ECSRenderSystem() {}
	};

	template<typename ...Requirements>
	inline ECSRenderSystem<Requirements...>::ECSRenderSystem()
	{
		this->requirements = { Requirements::ID... };
		this->componentBitset = 0;
		for (ComponentID id : this->requirements)
			Utils::setBit<ComponentBitset>(this->componentBitset, id);
	}
}

#endif
