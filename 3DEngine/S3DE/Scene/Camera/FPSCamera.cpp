#include "FPSCamera.h"

#include "CameraConfig.h"
#include "../../Input/InputManager.h"
#include "SM/Maths.h"
#include "SM/MathsTransform.h"

#include "../../Utils/Utils.h"

s3de::FPSCamera::FPSCamera() : Camera()
{
	setName("FPSCamera[%id]");
}

s3de::FPSCamera::FPSCamera(const sm::Vec3 & direction, float aspectRatio) : Camera(direction, aspectRatio)
{
	setName("FPSCamera[%id]");
}

s3de::FPSCamera::FPSCamera(const sm::Vec3 & direction, const sm::Vec3 & position, float aspectRatio) : Camera(direction, position, aspectRatio)
{
	setName("FPSCamera[%id]");
}

s3de::FPSCamera::~FPSCamera()
{
}

void s3de::FPSCamera::update(GLFWwindow * window, float dt, int windowWidth, int windowHeight)
{
	sm::Vec2 mousePos = InputManager::getMousePosition(window);
	mousePos.x /= (float)windowWidth;
	mousePos.y /= (float)windowHeight;

	float stepX = windowWidth / CAMERA_WIDTH;
	float cameraHeight = windowWidth / windowHeight * CAMERA_WIDTH;
	float stepY = windowWidth / cameraHeight;
	
	if (s3de::InputManager::press(window, GLFW_KEY_W))
		setPosition(getPosition() + (FPS_CAMERA_SPEED * dt) * getDirection());
	if (s3de::InputManager::press(window, GLFW_KEY_S))
		setPosition(getPosition() - (FPS_CAMERA_SPEED * dt) * getDirection());
	if (s3de::InputManager::press(window, GLFW_KEY_D))
		setPosition(getPosition() + (FPS_CAMERA_SPEED * dt) * getRight());
	if (s3de::InputManager::press(window, GLFW_KEY_A))
		setPosition(getPosition() - (FPS_CAMERA_SPEED * dt) * getRight());

	static bool activated = false;
	if (s3de::InputManager::toggle(window, GLFW_KEY_C))
	{
		if (!activated)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			activated = true;
		}
		// Mouse position has changed!
		if (this->preMousePos != mousePos)
		{
			sm::Vec3 dir = getDirection();

			sm::Vec2 deltaPos = sm::Vec2(0.5f, 0.5f) - mousePos;
			dir = sm::MathsTransform::rotate(dir, MOUSE_SENSITIVITY_X * deltaPos.x * stepX * dt, getUp());
			dir = sm::MathsTransform::rotate(dir, MOUSE_SENSITIVITY_Y * deltaPos.y * stepY * dt, getRight());
			lookIn(dir);
			glfwSetCursorPos(window, (float)windowWidth / 2, (float)windowHeight / 2);

		}
	}
	else if (activated)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		activated = false;
	}

	this->preMousePos = mousePos;
}
