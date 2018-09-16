#include "Display.h"

#include "WindowConfig.h"
#include "../../Utils/Error.h"

s3de::Display* s3de::Display::displayPtr = nullptr;

s3de::Display::Display()
{
	this->title = DEFAULT_WINDOW_TITLE;
	this->width = DEFAULT_WINDOW_WIDTH;
	this->height = DEFAULT_WINDOW_HEIGHT;
	init();
}

s3de::Display::Display(const std::string & title)
{
	this->title = title;
	this->width = DEFAULT_WINDOW_WIDTH;
	this->height = DEFAULT_WINDOW_HEIGHT;
	init();
}

s3de::Display::Display(const std::string & title, unsigned int width, unsigned int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
	init();
}

s3de::Display::~Display()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void s3de::Display::updateView(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	glViewport(0, 0, this->width, this->height);
}

void s3de::Display::setTitle(const std::string & title)
{
	this->title = title;
	glfwSetWindowTitle(this->window, this->title.c_str());
}

void s3de::Display::setTitleSuffix(const std::string & suffix)
{
	glfwSetWindowTitle(this->window, (this->title+suffix).c_str());
}

unsigned int s3de::Display::getWidth() const
{
	return this->width;
}

unsigned int s3de::Display::getHeight() const
{
	return this->height;
}

GLFWwindow * s3de::Display::getWindowPtr() const
{
	return this->window;
}

float s3de::Display::getAspectRatio() const
{
	return (float)this->width / (float)this->height;
}

void s3de::Display::init()
{
	Display::displayPtr = this;

	if (!glfwInit())
	{
		Error::printError("DISPLAY::init()", "Failed to initialize GLFW!");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Modern opengl
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Make MacOS happy
#endif

	this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
	if (this->window == NULL)
	{
		Error::printError("DISPLAY::init()", "Failed to open GLFW window!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1); // Enable vsync

	// --------------- INIT GLEW ---------------
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		Error::printError("DISPLAY::init()", "Failed to initialize GLEW!");
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, this->width, this->height);

	glfwSetWindowSizeCallback(this->window, resizeCallback);
}

void s3de::Display::resizeCallback(GLFWwindow * window, int width, int height)
{
	Display::displayPtr->updateView(width, height);
	Display::displayPtr->sizeUpdated = true;
}
