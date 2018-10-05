#ifndef S3DE_POSITION_COMPONENT_H
#define S3DE_POSITION_COMPONENT_H

#include "../Component.h"
#include "SM\Vectors\Vec3.h"

namespace s3de
{
	struct PositionComponent : public ECSComponent<PositionComponent>
	{
		sm::Vec3 position;
	};
}

#endif
