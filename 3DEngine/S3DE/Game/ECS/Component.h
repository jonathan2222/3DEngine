#ifndef S3DE_COMPONENT_H
#define S3DE_COMPONENT_H

#include <vector>

namespace s3de
{
	struct BaseComponent;
	typedef unsigned int(*CreateComponentFunction)(std::vector<unsigned char>& memory, void* entity, BaseComponent* comp);
	typedef void(*FreeComponentFunction)(BaseComponent* comp);

	struct BaseComponent
	{
		static unsigned int registerComponent(CreateComponentFunction createFunction, FreeComponentFunction freeFunction);

		void* entityPtr = nullptr;

		static CreateComponentFunction getCreateFunction(unsigned int id)
		{
			return (*componentTypes)[id].first;
		}

		static FreeComponentFunction getFreeFunction(unsigned int id)
		{
			return (*componentTypes)[id].second;
		}

	private:
		static std::vector<std::pair<CreateComponentFunction, FreeComponentFunction>>* componentTypes;
	};

	template<typename T>
	struct Component : BaseComponent
	{
		static CreateComponentFunction CREATE_FUNCTION;
		static FreeComponentFunction FREE_FUNCTION;
		static unsigned int SIZE;
		static unsigned int ID;
	};

	template<typename T>
	unsigned int createComponent(std::vector<unsigned char>& memory, void* entity, BaseComponent* comp)
	{
		unsigned int index = memory.size();
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
	unsigned int Component<T>::ID(registerComponent(Component<T>::CREATE_FUNCTION, Component<T>::FREE_FUNCTION));
}

#endif