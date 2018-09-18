#ifndef S3DE_COMPONENT_H
#define S3DE_COMPONENT_H

#include <vector>
#include <tuple>

#include "EcsDefines.h"

namespace s3de
{
	struct BaseComponent;
	typedef ComponentIndex(*CreateComponentFunction)(std::vector<Byte>& memory, EntityHandle entity, BaseComponent* comp);
	typedef void(*FreeComponentFunction)(BaseComponent* comp);

	struct BaseComponent
	{
		static unsigned int registerComponent(CreateComponentFunction createFunction, FreeComponentFunction freeFunction, unsigned int);

		EntityHandle entityHandle = nullptr;

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

	private:
		static std::vector<std::tuple<CreateComponentFunction, FreeComponentFunction, unsigned int>>* componentTypes;
	};

	template<typename T>
	struct Component : BaseComponent
	{
		static CreateComponentFunction CREATE_FUNCTION;
		static FreeComponentFunction FREE_FUNCTION;
		static unsigned int SIZE;
		static ComponentID ID;
	};

	template<typename T>
	ComponentIndex createComponent(std::vector<unsigned char>& memory, void* entity, BaseComponent* comp)
	{
		ComponentIndex index = memory.size();
		memory.resize(index + T::SIZE);
		// Allocate memory in 'memory' at position 'index' and fill it with data from comp. 
		T* component = new(&memory[index])T(*(T*)comp);
		component->entity = entity;
		return index;
	}

	template<typename T>
	void freeComponent(BaseComponent* comp)
	{
		T* component = (T*)comp;
		delete component;
	}

	template<typename T>
	CreateComponentFunction Component<T>::CREATE_FUNCTION(createComponent<T>);

	template<typename T>
	FreeComponentFunction Component<T>::FREE_FUNCTION(freeComponent<T>);

	template<typename T>
	unsigned int Component<T>::SIZE(sizeof(T));

	template<typename T>
	ComponentID Component<T>::ID(registerComponent(Component<T>::CREATE_FUNCTION, Component<T>::FREE_FUNCTION, sizeof(T)));
}

#endif