#include "IGame.h"

#include "../Utils/Error.h"
#include "../Utils/Timer.h"

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

void s3de::IGame::init()
{
	s3de::Error::init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	OnInitiate();

	s3de::Timer timer;
	float fpsDisplayTimer = 1.0f;

	glfwSetInputMode(display->getWindowPtr(), GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
	glfwSetInputMode(display->getWindowPtr(), GLFW_STICKY_KEYS, GL_TRUE);
	while (glfwGetKey(display->getWindowPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(display->getWindowPtr()) == 0)
	{
		timer.update();
		if (display->sizeUpdated)
		{
			// Update camera
			display->sizeUpdated = false;
		}

		// ----------------- Update -----------------
		OnFrameUpdate();

		// ----------------- Render -----------------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
}
