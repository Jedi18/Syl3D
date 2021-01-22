#include "entitycreator.h"

#include "../utility/fileio.h"
#include "../utility/modelfactory.h"
#include "../entity/cube.h"
#include "../entity/entityfactory.h"
#include "../texture/texturefactory.h"

#include "terraingenerator.h"
#include "texturemanager.h"
#include "objectlist.h"

using namespace gui;

std::vector<std::string> EntityCreator::modelFiles = std::vector<std::string>();
int EntityCreator::selectedModel = -1;
std::shared_ptr<entity::Model> EntityCreator::currentModel = nullptr;

void EntityCreator::Initialize() {
    modelFiles = utility::FileIO::filesInPath("resources/models");
}

void EntityCreator::displayEntityCreator() {
	EntityFactory* entityFactory = EntityFactory::entityFactory();
	TextureFactory* textureFactory = TextureFactory::textureFactory();
    std::shared_ptr<EntityContainer> entityContainer = entityFactory->entityContainer();
	
	ImGui::Text("Entity Creator");

    float n = (float)((int)EntityFactory::EntityType::IcoSphere + 1);
    for (int entityT = (int)EntityFactory::EntityType::Cube; entityT <= (int)EntityFactory::EntityType::IcoSphere; entityT++) {
        if (entityT > 0)
            ImGui::SameLine();
        ImGui::PushID(entityT);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(entityT / n, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(entityT / n, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(entityT / n, 0.8f, 0.8f));

        if (ImGui::Button(EntityFactory::ENTITY_NAMES[(EntityFactory::EntityType)entityT].c_str())) {
            std::shared_ptr<entity::Entity> ent = entityFactory->addEntity((EntityFactory::EntityType)entityT);
            entityContainer->setSelectedObject(ent);
        }

        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }

    ImGui::Text("Lights");
    n = (float)((int)EntityFactory::LightType::Point + 1);
    for (int lightT = (int)EntityFactory::LightType::Point; lightT <= (int)EntityFactory::LightType::Spot; lightT++) {
        if (lightT > 0)
            ImGui::SameLine();
        ImGui::PushID(lightT);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(lightT / n, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(lightT / n, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(lightT / n, 0.8f, 0.8f));

        if (ImGui::Button(EntityFactory::LIGHT_NAMES[(EntityFactory::LightType)lightT].c_str())) {
            std::shared_ptr<light::Light> light = entityFactory->addLight((EntityFactory::LightType)lightT);
            entityContainer->setSelectedObject(light);
        }

        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }

    displayModelSelector();

    if (ImGui::Button("Terrain Generator")) {
        TerrainGenerator::open = true;
    }
    TerrainGenerator::ShowTerrainGenerator();

    if (ImGui::Button("Texture Manager")) {
        TextureManager::open = true;
    }
    TextureManager::ShowTextureManager();

    if (ImGui::Button("Object List")) {
        ObjectList::open = true;
    }
    ObjectList::ShowObjectList();

    ImGui::Separator();
}

void EntityCreator::displayModelSelector() {
    if (ImGui::TreeNode("Load Models")) {
        for (int i = 0; i < modelFiles.size(); i++) {
            if (ImGui::Selectable(modelFiles[i].c_str(), selectedModel == i)) {
                if (i == selectedModel) {
                    continue;
                }

                selectedModel = i;
                currentModel = utility::ModelFactory::loadModel("resources/models/" + modelFiles[selectedModel] + "/" + modelFiles[selectedModel] + ".obj", "modelShader");
                EntityFactory::entityFactory()->entityContainer()->addEntity(currentModel);
            }
        }

        ImGui::TreePop();
    }
}