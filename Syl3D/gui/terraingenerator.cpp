#include "terraingenerator.h"

#include "../utility/heightmapgenerator.h"
#include "../entity/entityfactory.h"
#include "../entity/entitycontainer.h"
#include "../texture/texturefactory.h"

using namespace gui;

bool TerrainGenerator::open = false;
std::shared_ptr<entity::Terrain> TerrainGenerator::currentTerrain = nullptr;
int TerrainGenerator::rows = 10;
int TerrainGenerator::cols = 10;
float TerrainGenerator::frequency = 0.8f;

void TerrainGenerator::ShowTerrainGenerator() {
    if (!TerrainGenerator::open) {
        return;
    }

    ImGui::Begin("Terrain Generator", &open);
    
    ImGui::SliderInt("Rows", &rows, 1, 100);
    ImGui::SliderInt("Columns", &cols, 1, 100);
    ImGui::SliderFloat("Frequency", &frequency, 0.1f, 2.0f, "%.3f");

    if (ImGui::Button("Generate")) {
        utility::HeightmapData heightmapData = utility::HeightmapGenerator::ProceduralHeightmap(rows, cols, frequency);

        std::shared_ptr<TextureMaterial> terrainTex = TextureFactory::textureFactory()->getTextureMaterial("terrainTex");

        currentTerrain = std::make_shared<entity::Terrain>(heightmapData);
        currentTerrain->setTexture(terrainTex);
        currentTerrain->translateTo(math::Vec3(0.0f, -5.0f, 0.0f));
        currentTerrain->scale(20);

        std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
        entityContainer->addEntity(currentTerrain);
    }

    if (ImGui::Button("Delete current terrain")) {
        if (currentTerrain != nullptr) {
            std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
            entityContainer->deleteEntity(currentTerrain);
            currentTerrain = nullptr;
        }
    }

    ImGui::End();
}