#ifndef S3DE_FPS_CAMERA_H
#define S3DE_FPS_CAMERA_H

#include "Camera.h"

#include "SM/Vectors/Vec2.h"
#include "SM/Vectors/Vec3.h"

namespace s3de
{
	class FPSCamera	: public Camera
	{
	public:
		FPSCamera();
		FPSCamera(const sm::Vec3& direction, float aspectRatio);
		FPSCamera(const sm::Vec3& direction, const sm::Vec3& position, float aspectRatio);
		virtual ~FPSCamera();

		void update(GLFWwindow* window, float dt, int windowWidth, int windowHeight) override;

	private:
		sm::Vec2 preMousePos;
	};
}

#endif
