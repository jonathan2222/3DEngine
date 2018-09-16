#ifndef S3DE_CAMERA_CONFIG_H
#define S3DE_CAMERA_CONFIG_H

#include "SM/Maths.h"

namespace s3de
{
	static const float DEFAULT_FOV			= sm::MathsConstatns::PI / 4.0f; // 45 deg
	static const float DEFAULT_ZNEAR		= 0.1f;
	static const float DEFAULT_ZFAR			= 100.0f;

	static const float CAMERA_WIDTH			= 600.0f;
	static const float FPS_CAMERA_SPEED		= 10.0f;
	static const float MOUSE_SENSITIVITY_X	= 100.0f;
	static const float MOUSE_SENSITIVITY_Y	= 100.0f;
}

#endif
