#include "Component.h"

// TODO: Delete this when not used!!
std::vector<std::pair<s3de::CreateComponentFunction, s3de::FreeComponentFunction>>* s3de::BaseComponent::componentTypes = nullptr;

unsigned int s3de::BaseComponent::registerComponent(CreateComponentFunction createFunction, FreeComponentFunction freeFunction)
{
	if (componentTypes == nullptr)
	{
		componentTypes = new std::vector<std::pair<s3de::CreateComponentFunction, s3de::FreeComponentFunction>>();
	}
	// Allow us to have access to how to create and destroy the specific component from outside its class.
	std::pair<s3de::CreateComponentFunction, s3de::FreeComponentFunction> data;
	data.first = createFunction;
	data.second = freeFunction;
	componentTypes->push_back(data);
	return componentTypes->size()-1;
}
