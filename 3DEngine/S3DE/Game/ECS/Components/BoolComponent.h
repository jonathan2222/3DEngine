#ifndef S3DE_BOOL_COMPONENT_H
#define S3DE_BOOL_COMPONENT_H

#include "../Component.h"

namespace s3de
{
	struct BoolComponent : public ECSComponent<BoolComponent>
	{
		bool b;
	};
}

#endif
