#include "System.h"

unsigned int s3de::ISystem::counter = 0;

unsigned int s3de::ISystem::registerSystem()
{
	return s3de::ISystem::counter++;
}
