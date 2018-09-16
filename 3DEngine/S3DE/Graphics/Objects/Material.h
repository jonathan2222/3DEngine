#ifndef S3DE_MATERIAL_H
#define S3DE_MATERIAL_H

#include "SM/Vectors/Vec4.h"

namespace s3de
{
	namespace Material
	{
		struct MaterialData
		{
			sm::Vec4 ambientColor;
			sm::Vec4 diffuseColor;
			sm::Vec4 specularColor;
		};
	}
}

#endif
