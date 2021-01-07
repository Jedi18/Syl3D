#include "entityeditor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../math/rotation.h"

#include "entityinfovisitor.h"
#include "../entity/entitymanager.h"

#include "texturemanager.h"
#include "../texture/texturefactory.h"

using namespace gui;

int EntityEditor::_selectedTexture = 0;
bool EntityEditor::entityTextureUpdated = false;
std::shared_ptr<entity::Entity> EntityEditor::currentEntity = nullptr;

void EntityEditor::displayEntityEditor(std::shared_ptr<entity::Entity> selectedEntity) {
	if (currentEntity == nullptr || currentEntity != selectedEntity) {
		entityTextureUpdated = false;
		currentEntity = selectedEntity;
	}

	ImGui::Text("Entity Editor");

	if (selectedEntity == nullptr) {
		ImGui::Text("No entity selected.");
		return;
	}

	ImGui::Separator();

	/* Entity specific info */
	EntityInfoVisitor::EntityInfo entityInfo;
	EntityInfoVisitor entityInfoVisitor;
	selectedEntity->accept(entityInfoVisitor);
	entityInfo = entityInfoVisitor.getData();

	ImGui::Text(entityInfo.entityTypeName.c_str());

	ImGui::Separator();
	// Common entity data like location, rotation, scale
	math::Vec3 entityPosition = selectedEntity->position();
	math::Vec3 entityScale = selectedEntity->getScale();
	math::Vec3 entityRotation = math::Rotation::MatToEulerAngles(selectedEntity->rotation());

	ImGui::LabelText("Entity ID", std::to_string(selectedEntity->id()).c_str());

	float posvec[4] = {entityPosition.x, entityPosition.y, entityPosition.z};
	if (ImGui::DragFloat3("Position", posvec, 0.01f, -1000.0f, 1000.0f)) {
		selectedEntity->translateTo(math::Vec3(posvec[0], posvec[1], posvec[2]));
	}

	float scalevec[4] = { entityScale.x, entityScale.y, entityScale.z };
	if (ImGui::DragFloat3("Scale", scalevec, 0.01f, -1000.0f, 1000.0f)) {
		selectedEntity->setScale(math::Vec3(scalevec[0], scalevec[1], scalevec[2]));
	}

	float rotvec[4] = { entityRotation.x, entityRotation.y, entityRotation.z };
	if (ImGui::SliderFloat3("Rotation", rotvec, -3.14f, 3.14f)) {
		selectedEntity->setRotation(glm::eulerAngleYXZ(rotvec[1], rotvec[0], rotvec[2]));
	}

	ImGui::Separator();

	if (!entityTextureUpdated) {
		std::vector<std::string> textureMaterialsList = TextureFactory::getAvailableTextureMaterials();
		std::string textureName = TextureFactory::getTextureMaterialName(selectedEntity->texture());
		for (int i = 0; i < textureMaterialsList.size(); i++) {
			if (textureMaterialsList[i] == textureName) {
				_selectedTexture = i;
				break;
			}
		}

		entityTextureUpdated = true;
	}

	TextureManager::textureMaterialsListGUI(textureSelectedCallback, _selectedTexture);
}

void EntityEditor::textureSelectedCallback(int selectedTexture) {
	if (currentEntity != nullptr) {
		std::vector<std::string> textureMaterialsList = TextureFactory::getAvailableTextureMaterials();
		entity::EntityManager* entityManager = entity::EntityManager::entityManager();
		entityManager->changeTexture(currentEntity, TextureFactory::getTextureMaterial(textureMaterialsList[selectedTexture]));
		entityTextureUpdated = false;
	}
}