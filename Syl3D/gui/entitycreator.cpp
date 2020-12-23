#include "entitycreator.h"

#include "../entity/cube.h"
#include "../entity/entityfactory.h"
#include "../texture/texturefactory.h"

using namespace gui;

void EntityCreator::displayEntityCreator() {
	EntityFactory* entityFactory = EntityFactory::entityFactory();
	TextureFactory* textureFactory = TextureFactory::textureFactory();
    std::shared_ptr<EntityContainer> entityContainer = entityFactory->entityContainer();
	
	ImGui::Text("Entity Creator");

	/*if (ImGui::Button("Cube")) {
		std::shared_ptr<entity::Entity> cube = entityFactory->addEntity(EntityFactory::EntityType::Cube);
		cube->translateTo(math::Vec3(0.0f, 0.0f, 0.0f));
		cube->scale(5);
	}*/

    float n = (float)((int)EntityFactory::EntityType::Terrain + 1);
    for (int entityT = (int)EntityFactory::EntityType::Cube; entityT <= (int)EntityFactory::EntityType::Terrain; entityT++) {
        if (entityT > 0)
            ImGui::SameLine();
        ImGui::PushID(entityT);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(entityT / n, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(entityT / n, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(entityT / n, 0.8f, 0.8f));

        if (ImGui::Button(EntityFactory::ENTITY_NAMES[(EntityFactory::EntityType)entityT].c_str())) {
            std::shared_ptr<entity::Entity> ent = entityFactory->addEntity((EntityFactory::EntityType)entityT);
            entityContainer->setSelectedEntity(ent);
        }

        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }

    ImGui::Separator();
}