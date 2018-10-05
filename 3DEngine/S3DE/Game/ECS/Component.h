#ifndef S3DE_COMPONENT_H
#define S3DE_COMPONENT_H

#include <vector>
#include <tuple>

#include "EcsDefines.h"

namespace s3de
{
	struct Entity;
	struct ECSBaseComponent;
	typedef ComponentIndex(*CreateComponentFunction)(std::vector<Byte>& memory, Entity* entity, ECSBaseComponent* comp);
	typedef void(*FreeComponentFunction)(ECSBaseComponent* comp);

	struct ECSBaseComponent
	{
		Entity* entity = nullptr;

		static unsigned int registerComponent(CreateComponentFunction createFunction, FreeComponentFunction freeFunction, unsigned int);

		static CreateComponentFunction getCreateFunction(unsigned int id)
		{
			return std::get<0>((*componentTypes)[id]);
		}

		static FreeComponentFunction getFreeFunction(unsigned int id)
		{
			return std::get<1>((*componentTypes)[id]);
		}

		static unsigned int getSize(unsigned int id)
		{
			return std::get<2>((*componentTypes)[id]);
		}

		static void deleteComponentTypes()
		{
			if (componentTypes != nullptr)
				delete componentTypes;
			componentTypes = nullptr;
		}

	private:
		static std::vector<std::tuple<CreateComponentFunction, FreeComponentFunction, unsigned int>>* componentTypes;
	};

	template<typename T>
	struct ECSComponent : ECSBaseComponent
	{
		static CreateComponentFunction CREATE_FUNCTION;
		static FreeComponentFunction FREE_FUNCTION;
		static unsigned int SIZE;
		static ComponentID ID;
	};

	template<typename T>
	ComponentIndex createComponent(std::vector<unsigned char>& memory, Entity* entity, ECSBaseComponent* comp)
	{
		ComponentIndex index = memory.size();
		memory.resize(index + T::SIZE);
		// Copy component data to 'memory' at position 'index'.
		T* component = new(&memory[index])T(*(T*)comp);
		component->entity = entity;
		return index;
	}

	template<typename T>
	void freeComponent(ECSBaseComponent* comp)
	{
		T* component = (T*)comp;
		//delete component;
		component->~T();
	}

	template<typename T>
	CreateComponentFunction ECSComponent<T>::CREATE_FUNCTION(createComponent<T>);

	template<typename T>
	FreeComponentFunction ECSComponent<T>::FREE_FUNCTION(freeComponent<T>);

	template<typename T>
	unsigned int ECSComponent<T>::SIZE(sizeof(T));

	template<typename T>
	ComponentID ECSComponent<T>::ID(registerComponent(ECSComponent<T>::CREATE_FUNCTION, ECSComponent<T>::FREE_FUNCTION, sizeof(T)));
}

#endif