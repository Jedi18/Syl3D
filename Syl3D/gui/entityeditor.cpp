#include "entityeditor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../math/rotation.h"

#include "objectlist.h"
#include "objectinfovisitor.h"
#include "objectguivisitor.h"
#include "../lights/light.h"
#include "../entity/entitymanager.h"

#include "texturemanager.h"
#include "../texture/texturefactory.h"

using namespace gui;

int EntityEditor::_selectedTexture = 0;
bool EntityEditor::entityTextureUpdated = false;
bool EntityEditor::isCurrentObjectAnEntity = false;
std::shared_ptr<Object> EntityEditor::currentObject = nullptr;

void EntityEditor::displayEntityEditor(std::shared_ptr<Object> selectedObject) {
	if (currentObject == nullptr || currentObject->id() != selectedObject->id()) {
		entityTextureUpdated = false;
		currentObject = selectedObject;
		isCurrentObjectAnEntity = (std::dynamic_pointer_cast<entity::Entity>(selectedObject) != nullptr);
		ObjectList::setSelectedObject(currentObject->id());
	}

	ImGui::Text("Entity Editor");

	if (selectedObject == nullptr) {
		ImGui::Text("No entity selected.");
		return;
	}

	ImGui::Separator();

	/* Entity specific info */
	ObjectInfoVisitor::ObjectInfo objectInfo;
	ObjectInfoVisitor entityInfoVisitor;

	std::shared_ptr<entity::Entity> selectedEntity = std::dynamic_pointer_cast<entity::Entity>(selectedObject);
	std::shared_ptr<light::Light> selectedLight = std::dynamic_pointer_cast<light::Light>(selectedObject);
	if (selectedEntity != nullptr) {
		selectedEntity->accept(entityInfoVisitor);
		objectInfo = entityInfoVisitor.getData();
	}
	else {
		selectedLight->accept(entityInfoVisitor);
		objectInfo = entityInfoVisitor.getData();
	}

	ImGui::Text(objectInfo.entityTypeName.c_str());

	ImGui::Separator();
	// Common entity data like location, rotation, scale
	math::Vec3 entityPosition = selectedObject->position();
	math::Vec3 entityScale = selectedObject->getScale();
	math::Vec3 entityRotation = math::Rotation::MatToEulerAngles(selectedObject->rotation());

	ImGui::LabelText("Object ID", std::to_string(selectedObject->id()).c_str());

	float posvec[4] = {entityPosition.x, entityPosition.y, entityPosition.z};
	if (ImGui::DragFloat3("Position", posvec, 0.01f, -1000.0f, 1000.0f)) {
		selectedObject->translateTo(math::Vec3(posvec[0], posvec[1], posvec[2]));
	}

	float scalevec[4] = { entityScale.x, entityScale.y, entityScale.z };
	if (ImGui::DragFloat3("Scale", scalevec, 0.01f, -1000.0f, 1000.0f)) {
		selectedObject->setScale(math::Vec3(scalevec[0], scalevec[1], scalevec[2]));
	}

	float rotvec[4] = { entityRotation.x, entityRotation.y, entityRotation.z };
	if (ImGui::SliderFloat3("Rotation", rotvec, -3.14f, 3.14f)) {
		selectedObject->setRotation(glm::eulerAngleYXZ(rotvec[1], rotvec[0], rotvec[2]));
	}

	ImGui::Separator();

	ObjectGUIVisitor objectGUIvisitor;
	if (selectedEntity != nullptr) {
		selectedEntity->accept(objectGUIvisitor);
	}
	else {
		selectedLight->accept(objectGUIvisitor);
	}

	if (isCurrentObjectAnEntity) {
		if (!entityTextureUpdated) {
			std::vector<std::string> textureMaterialsList = TextureFactory::getAvailableTextureMaterials();
			std::shared_ptr<entity::Entity> selectedEntity = std::dynamic_pointer_cast<entity::Entity>(selectedObject);
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
}

void EntityEditor::textureSelectedCallback(int selectedTexture) {
	if (currentObject != nullptr && isCurrentObjectAnEntity) {
		std::vector<std::string> textureMaterialsList = TextureFactory::getAvailableTextureMaterials();
		entity::EntityManager* entityManager = entity::EntityManager::entityManager();
		entityManager->changeTexture(std::dynamic_pointer_cast<entity::Entity>(currentObject), TextureFactory::getTextureMaterial(textureMaterialsList[selectedTexture]));
		entityTextureUpdated = false;
	}
}