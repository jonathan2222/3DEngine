#include "Component.h"

std::vector<std::tuple<s3de::CreateComponentFunction, s3de::FreeComponentFunction, unsigned int>>* s3de::BaseComponent::componentTypes = nullptr;

unsigned int s3de::BaseComponent::registerComponent(CreateComponentFunction createFunction, FreeComponentFunction freeFunction, unsigned int size)
{
	if (componentTypes == nullptr)
	{
		componentTypes = new std::vector<std::tuple<s3de::CreateComponentFunction, s3de::FreeComponentFunction, unsigned int>>();
	}
	// Allow us to have access to how to create and destroy the specific component from outside its class.
	ComponentID id = componentTypes->size();
	componentTypes->push_back(std::tuple<s3de::CreateComponentFunction, s3de::FreeComponentFunction, unsigned int>(createFunction, freeFunction, size));
	return id;
}
