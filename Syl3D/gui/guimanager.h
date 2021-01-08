#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace gui
{
	class GUIManager
	{
	public:
		void initialize(GLFWwindow* window);

		void render();

		void cleanUp();

		void toolsMenu();

		bool mouseOnGUI() const;

	private:
		const char* glsl_version = "#version 330";
		bool show_demo_window = true;
	};
}

