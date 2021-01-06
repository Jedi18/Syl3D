#pragma once

#include <vector>
#include <string>
#include <functional>

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace gui
{
	class TextureManager
	{
	public:
		static void ShowTextureManager();

		static void textureMaterialsListGUI(std::function<void(int)> callbackFunc, int& selectedTexture);

	private:
		static std::string getTextureMaterialsList(const std::vector<std::string>& textureMaterialsList);

		static void textureSelectedCallback(int selectedTex);

	public:
		static bool open;
		static int _selectedTexture;
	};
}
