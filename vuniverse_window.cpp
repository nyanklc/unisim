#include "vuniverse_window.h"

#include <stdexcept>

vuniverse::VuniverseWindow::VuniverseWindow(int w, int h, std::string name)
{
	_w = w;
	_h = h;
	_name = name;
}

vuniverse::VuniverseWindow::~VuniverseWindow()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void vuniverse::VuniverseWindow::initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(_w, _h, _name.c_str(), nullptr, nullptr);
}

void vuniverse::VuniverseWindow::pollEvents()
{
	glfwPollEvents();
}

bool vuniverse::VuniverseWindow::shouldClose()
{
	return glfwWindowShouldClose(_window);
}

void vuniverse::VuniverseWindow::createWindowSurface(VkInstance& instance, VkSurfaceKHR* surface)
{
	if (glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface");
	}
}
