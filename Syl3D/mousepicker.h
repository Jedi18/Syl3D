#pragma once

#include "freecamera.h"

class MousePicker
{
public:
	MousePicker(FreeCamera* freeCam);

	glm::vec3 calculateMouseRay(float mouseX, float mouseY);

private:
	glm::vec4 clipToEyeCoords(glm::vec4 clipCoords) const;

	glm::vec3 eyeToWorldCoords(glm::vec4 eyeCoords) const;

private:
	FreeCamera* _freeCamera;
};