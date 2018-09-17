#include "IGame.h"

#include "../Utils/Error.h"
#include "../Utils/Timer.h"

#include "../Graphics/Objects/Model.h"
#include "../Utils/ModelLoader.h"
#include "../Utils/ModelGenerator.h"
#include "../Graphics/Rendering/Renderer.h"
#include "../Graphics/Shaders/Shader.h"

#include "SM\Maths.h"
#include "SM\MathsTransform.h"

#include "../Scene/Camera/FPSCamera.h"
#include "../Input/InputManager.h"

s3de::IGame::IGame()
{
	this->display = new Display();
	init();
}

s3de::IGame::IGame(const std::string & title, unsigned int width, unsigned int height)
{
	this->display = new Display(title, width, height);
	init();
}

s3de::IGame::~IGame()
{
	delete this->display;
}

void s3de::IGame::run()
{
	this->OnInitiate();
	loop();
}

void s3de::IGame::init()
{
	s3de::Error::init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void s3de::IGame::loop()
{
	s3de::Model* sphere = s3de::ModelGenerator::generateSphere();

	s3de::Model* barrel = s3de::ModelLoader::loadModel("./../3DEngine/S3DE/Resources/Models/Barrel.fbx");

	s3de::FPSCamera camera(sm::Vec3(0.0f, 0.0f, -1.0f), sm::Vec3(0.0f, 0.0f, 5.0f), display->getAspectRatio());
	glfwSetCursorPos(display->getWindowPtr(), display->getWidth() / 2, display->getHeight() / 2);

	s3de::Renderer renderer;
	renderer.setWireframe(false);
	s3de::Shader shader = renderer.getShader();

	sm::Mat4 world = sm::MathsTransform::translate(0.0f, 0.5f, -2.0f);

	s3de::Timer timer;
	float fpsDisplayTimer = 1.0f;
	int activeState = 0;
	glfwSetInputMode(display->getWindowPtr(), GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
	glfwSetInputMode(display->getWindowPtr(), GLFW_STICKY_KEYS, GL_TRUE);
	while (glfwGetKey(display->getWindowPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(display->getWindowPtr()) == 0)
	{
		timer.update();
		if (display->sizeUpdated)
		{
			// Update camera
			camera.setAspectRatio(display->getAspectRatio());
			camera.updateProj();
			display->sizeUpdated = false;
		}

		if (s3de::InputManager::toggle(display->getWindowPtr(), GLFW_KEY_C))
		{
			if (activeState != 1)
			{
				glfwSetCursorPos(display->getWindowPtr(), display->getWidth() / 2, display->getHeight() / 2);
				glfwSetInputMode(display->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			camera.update(display->getWindowPtr(), timer.getDeltaTime(), display->getWidth(), display->getHeight());
			glfwSetCursorPos(display->getWindowPtr(), display->getWidth() / 2, display->getHeight() / 2);
			activeState = 1;
		}
		else
		{
			if (activeState != 2)
				glfwSetInputMode(display->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			activeState = 2;
		}

		// ----------------- Update -----------------
		this->OnFrameUpdate();

		// ----------------- Render -----------------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.resetMaterial(); // Use default material

		sm::Quaternion baseRotation2(timer.getDeltaTime(), sm::Vec3(0.0f, 1.0f, 0.0f));
		world = baseRotation2.getMatrix4() * world;

		shader.bind();
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(world)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(sphere);

		sm::Quaternion baseRotation(-sm::MathsConstatns::PI / 2.0f, sm::Vec3(1.0f, 0.0f, 0.0f));
		sm::Mat4 w = baseRotation.getMatrix4();
		shader.bind();
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(w)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(barrel);

		// --------------- Display FPS --------------
		if (fpsDisplayTimer >= 1.0)
		{
			display->setTitleSuffix(" FPS: " + std::to_string(1.0 / timer.getDeltaTime()));
			fpsDisplayTimer = 0.0;
		}
		else fpsDisplayTimer += timer.getDeltaTime();

		glfwSwapBuffers(display->getWindowPtr());
		glfwPollEvents();
	}
	delete sphere;
	delete barrel;
}
