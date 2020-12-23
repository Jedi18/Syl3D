#include "heightmapgenerator.h"

#include "../vendor/stb_image/stb_image.h"
#include "../math/perlinnoise.h"

#include <iostream>

using namespace utility;

HeightmapData HeightmapGenerator::ProceduralHeightmap(const unsigned int rows, const unsigned int cols, const double frequency) {
    const double fx = rows / frequency;
    const double fy = cols / frequency;

    HeightmapData heightmapData;
    heightmapData.heightmap = new float[(size_t)(rows + 1) * (size_t)(cols + 1)];
    heightmapData.rows = rows;
    heightmapData.cols = cols;
    heightmapData.tilingX = rows;
    heightmapData.tilingY = cols;

    int index = 0;
    for (int i = 0; i <= cols; i++) {
        for (int j = 0; j <= rows; j++) {
            heightmapData.heightmap[index] = math::PerlinNoise::noise2D(i / fx, j / fy);
            index++;
        }
    }

    return heightmapData;
}

HeightmapData HeightmapGenerator::LoadHeightmapFromFile(const std::string& heightmapFile) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(heightmapFile.c_str(), &width, &height, &nrChannels, 0);

    HeightmapData heightmapData;
    heightmapData.rows = width;
    heightmapData.cols = height;
    heightmapData.tilingX = 1;
    heightmapData.tilingY = 1;

    heightmapData.heightmap = new float[(size_t)width * (size_t)height];
    if (data) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int index = j + i * width;
                heightmapData.heightmap[index] = (data[index * nrChannels] / 255.0f);
            }
        }
    }
    else {
        std::cout << "Failed to load the texture" << std::endl;
    }

    stbi_image_free(data);
    return heightmapData;
}