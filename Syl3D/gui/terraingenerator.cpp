#include "terraingenerator.h"

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

void TerrainGenerator::Initialize() {
    terrainFoldersList = utility::FileIO::filesInPath("resources/terrains");
}

void TerrainGenerator::ShowTerrainGenerator() {
    if (!TerrainGenerator::open) {
        return;
    }

    ImGui::Begin("Terrain Generator", &open);
    
    ImGui::SliderInt("Rows", &rows, 1, 100);
    ImGui::SliderInt("Columns", &cols, 1, 100);
    ImGui::SliderFloat("Frequency", &frequency, 0.1f, 2.0f, "%.3f");

    if (ImGui::Button("Generate")) {
        deleteCurrentTerrain();

        utility::HeightmapData heightmapData = utility::HeightmapGenerator::ProceduralHeightmap(rows, cols, frequency);
        std::shared_ptr<TextureMaterial> terrainTex = TextureFactory::textureFactory()->getTextureMaterial("terrainTex");

        currentTerrain = std::make_shared<entity::Terrain>(heightmapData);
        currentTerrain->setTexture(terrainTex);
        currentTerrain->translateTo(math::Vec3(0.0f, -5.0f, 0.0f));
        currentTerrain->scale(20);
        selectedTerrain = -1;

        std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
        entityContainer->addEntity(currentTerrain);
    }

    if (ImGui::Button("Delete current terrain")) {
        deleteCurrentTerrain();
    }

    ImGui::Separator();
    TerrainGenerator::ShowTerrainSelector();
    ImGui::End();
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
}

void TerrainGenerator::deleteCurrentTerrain() {
    if (currentTerrain != nullptr) {
        std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
        entityContainer->deleteEntity(currentTerrain);
        currentTerrain = nullptr;
        selectedTerrain = -1;
    }
}