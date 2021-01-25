#include "terraingenerator.h"

#include "../math/perlinnoise.h"
#include "../utility/fileio.h"
#include "../utility/heightmapgenerator.h"
#include "../entity/entityfactory.h"
#include "../entity/entitycontainer.h"
#include "../texture/texturefactory.h"

using namespace gui;

bool TerrainGenerator::open = false;
std::shared_ptr<entity::Terrain> TerrainGenerator::currentTerrain = nullptr;
std::vector<std::string> TerrainGenerator::terrainFoldersList = std::vector<std::string>();
int TerrainGenerator::selectedTerrain = -1;
int TerrainGenerator::rows = 10;
int TerrainGenerator::cols = 10;
float TerrainGenerator::frequency = 0.8f;
float TerrainGenerator::persistence = 0.5f;
int TerrainGenerator::octaves = 8;

void TerrainGenerator::Initialize() {
    terrainFoldersList = utility::FileIO::filesInPath("resources/terrains");
}

void TerrainGenerator::ShowTerrainGenerator() {
    if (!TerrainGenerator::open) {
        if (currentTerrain != nullptr) {
            deleteCurrentTerrain();
        }
        return;
    }

    ImGui::Begin("Terrain Generator", &open);
    TerrainGenerator::ShowGenerateTerrain();
    ImGui::Separator();
    TerrainGenerator::ShowTerrainSelector();
    ImGui::End();
}

void TerrainGenerator::ShowGenerateTerrain() {
    if (ImGui::TreeNode("Generate Terrain")) {
        if (currentTerrain == nullptr) {
            updateTerrain();
        }

        TerrainGenerator::ShowPerlinNoiseOptions();

        if (ImGui::SliderInt("Rows", &rows, 1, 100)) {
            updateTerrain();
        }

        if (ImGui::SliderInt("Columns", &cols, 1, 100)) {
            updateTerrain();
        }

        if (ImGui::SliderFloat("Frequency", &frequency, 0.1f, 2.0f, "%.3f")) {
            updateTerrain();
        }

        if (ImGui::Button("Generate")) {
            updateTerrain();
        }

        ImGui::TreePop();
    }
}

void TerrainGenerator::ShowTerrainSelector() {
    ImGui::Text("Load Terrain");

    if (ImGui::TreeNode("Available Terrains")) {
        for (int i = 0; i < terrainFoldersList.size(); i++) {
            if (ImGui::Selectable(terrainFoldersList[i].c_str(), selectedTerrain == i)) {
                if (i == selectedTerrain) {
                    continue;
                }

                deleteCurrentTerrain();
                selectedTerrain = i;
                currentTerrain = EntityFactory::entityFactory()->loadTerrain(terrainFoldersList[selectedTerrain]);
            }
        }

        ImGui::TreePop();
    }

    if (ImGui::Button("Finish")) {
        currentTerrain = nullptr;
        open = false;
    }
}

void TerrainGenerator::ShowPerlinNoiseOptions() {
    if (ImGui::TreeNode("Perlin Noise Options")) {
        if (ImGui::SliderFloat("Persistence", &persistence, 0.0f, 1.0f, "%.3f")) {
            updateTerrain();
        }

        if (ImGui::SliderInt("Octaves", &octaves, 1, 20)) {
            updateTerrain();
        }

        ImGui::TreePop();
    }
}

void TerrainGenerator::updateTerrain() {
    deleteCurrentTerrain();

    math::PerlinNoise::setPersistence(persistence);
    math::PerlinNoise::setOctaves(octaves);

    utility::HeightmapData heightmapData = utility::HeightmapGenerator::ProceduralHeightmap(rows, cols, frequency);
    std::shared_ptr<TextureMaterial> defaultTex = TextureFactory::textureFactory()->getTextureMaterial("default");

    currentTerrain = std::make_shared<entity::Terrain>(heightmapData);
    currentTerrain->setTexture(defaultTex);
    currentTerrain->translateTo(math::Vec3(0.0f, -5.0f, 0.0f));
    currentTerrain->scale(20);
    selectedTerrain = -1;

    std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
    entityContainer->addEntity(currentTerrain);
}

void TerrainGenerator::deleteCurrentTerrain() {
    if (currentTerrain != nullptr) {
        std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
        entityContainer->deleteEntity(currentTerrain);
        currentTerrain = nullptr;
        selectedTerrain = -1;
    }
}