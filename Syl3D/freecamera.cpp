#include "freecamera.h"

FreeCamera::FreeCamera() {
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 FreeCamera::viewMatrix() {
	glm::vec3 direction;
	direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction.y = sin(glm::radians(_pitch));
	direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	cameraFront = glm::normalize(direction);

	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void FreeCamera::mouseMovement(float xoffset, float yoffset) {
	xoffset *= _sensitivity;
	yoffset *= _sensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (_pitch > 89.0f) {
		_pitch = 89.0f;
	}

	if (_pitch < -89.0f) {
		_pitch = -89.0f;
	}
}

void FreeCamera::mouseScrolled(float xoffset, float yoffset) {
	_zoom -= yoffset;

	if (_zoom < 1.0f) {
		_zoom = 1.0f;
	}
	if (_zoom > 45.0f) {
		_zoom = 45.0f;
	}
}

void FreeCamera::keyboardInput(float dt, float zdir, float xdir) {
	cameraPos += (zdir * _cameraSpeed * dt) * cameraFront;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (xdir * _cameraSpeed * dt);
}

float FreeCamera::zoom() const {
	return _zoom;
}