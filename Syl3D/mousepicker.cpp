#include "mousepicker.h"

MousePicker::MousePicker(FreeCamera* freeCam) 
	:
	_freeCamera(freeCam)
{}

glm::vec3 MousePicker::calculateMouseRay(float mouseX, float mouseY) {
	float x = (2.0f * mouseX) / _freeCamera->windowWidth() - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / _freeCamera->windowHeight();
	glm::vec4 clipCoords(x, y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = clipToEyeCoords(clipCoords);
	return eyeToWorldCoords(eyeCoords);
}

glm::vec4 MousePicker::clipToEyeCoords(glm::vec4 clipCoords) const {
	glm::mat4 inversedProjection = glm::inverse(_freeCamera->projectionMatrix());
	glm::vec4 eyeCoords = inversedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec3 MousePicker::eyeToWorldCoords(glm::vec4 eyeCoords) const {
	glm::mat4 inversedView = glm::inverse(_freeCamera->viewMatrix());
	glm::vec4 rayWorld = inversedView * eyeCoords;
	glm::vec3 result = glm::normalize(glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z));
	return result;
}