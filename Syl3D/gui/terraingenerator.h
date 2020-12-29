#pragma once

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include "../entity/terrain.h"

namespace gui
{
	class TerrainGenerator
	{
	public:
        static void ShowTerrainGenerator();

	public:
		static bool open;

	private:
		static std::shared_ptr<entity::Terrain> currentTerrain;
		static int rows;
		static int cols;
		static float frequency;
	};

}

