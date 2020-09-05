#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FreeCamera
{
public:
	FreeCamera();

	glm::mat4 viewMatrix();

	glm::mat4 projectionMatrix();

	void mouseMovement(float xoffset, float yoffset);

	void mouseScrolled(float xoffset, float yoffset);

	void keyboardInput(float dt, float zdir, float xdir);

	float zoom() const;

	void updateWindowDimensions(float window_width, float window_height);

	float windowWidth() const;

	float windowHeight() const;

private:
	void recalculateProjectionMatrix();

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

	glm::mat4 _projection;

	float ASPECT_RATIO;
	const float NEAR = 0.1f;
	const float FAR = 100.0f;
	float WINDOW_WIDTH = 800.0f;
	float WINDOW_HEIGHT = 600.0f;
};