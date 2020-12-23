#include "entityeditor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../math/rotation.h"

#include "entityinfovisitor.h"

using namespace gui;

void EntityEditor::displayEntityEditor(std::shared_ptr<entity::Entity> selectedEntity) {
	ImGui::Text("Entity Editor");

	if (selectedEntity == nullptr) {
		ImGui::Text("No entity selected.");
		return;
	}

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
	/* Entity specific info */
	EntityInfoVisitor::EntityInfo entityInfo;
	EntityInfoVisitor entityInfoVisitor;
	selectedEntity->accept(entityInfoVisitor);
	entityInfo = entityInfoVisitor.getData();

	ImGui::Text(entityInfo.entityTypeName.c_str());
}