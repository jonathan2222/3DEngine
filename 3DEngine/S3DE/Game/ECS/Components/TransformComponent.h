#ifndef S3DE_TRANSFORM_COMPONENT_H
#define S3DE_TRANSFORM_COMPONENT_H

#include "../Component.h"
#include "SM\Matrices\Mat4.h"

namespace s3de
{
	struct TransformComponent : public Component<TransformComponent>
	{
		sm::Mat4 model;
		sm::Mat4 world;
	};
}

#endif
