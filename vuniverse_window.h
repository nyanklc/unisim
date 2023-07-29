#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace vuniverse
{
	class VuniverseWindow
	{
	public:
		VuniverseWindow(int w, int h, std::string name);
		VuniverseWindow(VuniverseWindow&) = delete;
		~VuniverseWindow();

		void operator=(VuniverseWindow&) = delete;
		
		void initialize();

		void pollEvents();
		bool shouldClose();

		void createWindowSurface(VkInstance &instance, VkSurfaceKHR *surface);

	private:
		GLFWwindow* _window;
		int _w;
		int _h;
		std::string _name;
	};
}