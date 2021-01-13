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
		static void Initialize();

        static void ShowTerrainGenerator();

		static void ShowTerrainSelector();

		static void ShowGenerateTerrain();

		static void ShowPerlinNoiseOptions();

	private:
		static void deleteCurrentTerrain();

		static void updateTerrain();

	public:
		static bool open;

	private:
		static std::shared_ptr<entity::Terrain> currentTerrain;
		static std::vector<std::string> terrainFoldersList;
		static int selectedTerrain;
		static int rows;
		static int cols;
		static float frequency;
		static float persistence;
		static int octaves;
	};

}

