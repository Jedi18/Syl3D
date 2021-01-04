#pragma once

#include <vector>
#include <string>

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace gui
{
	class TextureManager
	{
	public:
		static void ShowTextureManager();

	private:
		static std::string getTextureMaterialsList(const std::vector<std::string>& textureMaterialsList);

	public:
		static bool open;
		static int selectedTexture;
	};
}
