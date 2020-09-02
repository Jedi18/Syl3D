#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FreeCamera
{
public:
	FreeCamera();

	glm::mat4 viewMatrix();

	void mouseMovement(float xoffset, float yoffset);

	void mouseScrolled(float xoffset, float yoffset);

	void keyboardInput(float dt, float zdir, float xdir);

	float zoom() const;

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float _pitch = 0.0f;
	float _yaw = -90.0f;
	float _roll = 0.0f;
	float _zoom = 45.0f;
	const float _cameraSpeed = 5.0f;
	const float _sensitivity = 0.4f;
};