#pragma once

#include <string>

namespace utility
{
	struct HeightmapData
	{
		float* heightmap;
		unsigned int rows;
		unsigned int cols;
		float tilingX;
		float tilingY;
	};

	class HeightmapGenerator
	{
	public:
		static HeightmapData ProceduralHeightmap(const unsigned int rows, const unsigned int cols, const double frequency);

		static HeightmapData LoadHeightmapFromFile(const std::string& heightmapFile);
	};
}