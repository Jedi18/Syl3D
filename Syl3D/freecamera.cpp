#include "freecamera.h"

FreeCamera::FreeCamera() {
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	ASPECT_RATIO = WINDOW_WIDTH / WINDOW_HEIGHT;

	_projection = glm::mat4(1.0f);
	recalculateProjectionMatrix();
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

	if (yoffset != 0) {
		recalculateProjectionMatrix();
	}
}

void FreeCamera::keyboardInput(float dt, float zdir, float xdir) {
	cameraPos += (zdir * _cameraSpeed * dt) * cameraFront;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (xdir * _cameraSpeed * dt);
}

float FreeCamera::zoom() const {
	return _zoom;
}

glm::mat4 FreeCamera::projectionMatrix() {
	return _projection;
}

void FreeCamera::recalculateProjectionMatrix() {
	_projection = glm::perspective(glm::radians(_zoom), ASPECT_RATIO, NEAR, FAR);
}

void FreeCamera::updateWindowDimensions(float window_width, float window_height) {
	ASPECT_RATIO = window_width / window_height;
	WINDOW_WIDTH = window_width;
	WINDOW_HEIGHT = window_height;
	recalculateProjectionMatrix();
}

float FreeCamera::windowWidth() const {
	return WINDOW_WIDTH;
}

float FreeCamera::windowHeight() const {
	return WINDOW_HEIGHT;
}