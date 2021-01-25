#pragma once

#include <vector>
#include <string>

#include "../entity/model.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace gui
{
	class EntityCreator
	{
	public:
		static void Initialize();

		static void displayEntityCreator();

		static void displayModelSelector();

		static void displaySkyboxSelector();

	private:
		static std::vector<std::string> modelFiles;
		static int selectedModel;
		static int selectedSkybox;
		static std::shared_ptr<entity::Model> currentModel;
	};
}

