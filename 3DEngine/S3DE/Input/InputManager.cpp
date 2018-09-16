#include "InputManager.h"

#include "InputConfig.h"

std::unordered_map<int, std::pair<bool, int>> s3de::InputManager::keyMap = std::unordered_map<int, std::pair<bool, int>>();

bool s3de::InputManager::toggle(GLFWwindow* window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_TOGGLE);
	if (glfwGetKey(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first ^= 1;
	}
	else if (glfwGetKey(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	return keyMap[key].first;
}

bool s3de::InputManager::press(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_PRESS);
	return keyMap[key].first = glfwGetKey(window, key) == GLFW_PRESS;
}

bool s3de::InputManager::release(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_RELEASE);
	return keyMap[key].first = glfwGetKey(window, key) != GLFW_PRESS;
}

bool s3de::InputManager::click(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_CLICK);
	if (glfwGetKey(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first = true;
		return true;
	}
	else if (glfwGetKey(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	keyMap[key].first = false;
	return false;
}

sm::Vec2 s3de::InputManager::getMousePosition(GLFWwindow * window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return sm::Vec2((float)x, (float)y);
}

bool s3de::InputManager::mousePress(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_PRESS);
	return keyMap[key].first = glfwGetMouseButton(window, key) == GLFW_PRESS;
}

bool s3de::InputManager::mouseRelease(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_RELEASE);
	return keyMap[key].first = glfwGetMouseButton(window, key) != GLFW_PRESS;
}

bool s3de::InputManager::mouseToggle(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_TOGGLE);
	if (glfwGetMouseButton(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first ^= 1;
	}
	else if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	return keyMap[key].first;
}

bool s3de::InputManager::mouseClick(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, S3DE_KEY_CLICK);
	if (glfwGetMouseButton(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first = true;
		return true;
	}
	else if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	keyMap[key].first = false;
	return false;
}

bool s3de::InputManager::isKeyActive(int key)
{
	return keyMap[key].first;
}

bool s3de::InputManager::addKey(int key)
{
	if (keyMap.find(key) == keyMap.end())
	{
		keyMap.insert({ key, {false, S3DE_KEY_CLICK} });
		return true;
	}
	return false;
}

bool s3de::InputManager::setType(int key, int type)
{
	if ((keyMap[key].second & (0xFF-1)) != type)
	{
		keyMap[key].second = type;
		keyMap[key].first = false; // Reset active
		return true;
	}
	return false;
}
