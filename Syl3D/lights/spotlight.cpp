#include "spotlight.h"

using namespace light;

SpotLight::SpotLight(math::Vec3 position, math::Vec3 direction, shading::Color diffuse)
	:
	_position(position),
	_direction(direction),
	_diffuse(diffuse),
	_ambient(shading::Color(0.0f, 0.0f, 0.0f)),
	_specular(shading::Color(1.0f, 1.0f, 1.0f)),
	_constant(1.0f),
	_linearConstant(0.09f),
	_quadraticConstant(0.032f),
	_cutOff(glm::cos(glm::radians(12.5f))),
	_outerCutOff(glm::cos(glm::radians(17.5)))
{}

void SpotLight::setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) {
	shaderProgram->setVec3("spotLights[" + std::to_string(index) + "].position", _position);
	shaderProgram->setVec3("spotLights[" + std::to_string(index) + "].direction", _direction);
	shaderProgram->setColor3("spotLights[" + std::to_string(index) + "].ambient", _ambient);
	shaderProgram->setColor3("spotLights[" + std::to_string(index) + "].diffuse", _diffuse);
	shaderProgram->setColor3("spotLights[" + std::to_string(index) + "].specular", _specular);
	shaderProgram->setFloat("spotLights[" + std::to_string(index) + "].constant", _constant);
	shaderProgram->setFloat("spotLights[" + std::to_string(index) + "].linearConstant", _linearConstant);
	shaderProgram->setFloat("spotLights[" + std::to_string(index) + "].quadraticConstant", _quadraticConstant);
	shaderProgram->setFloat("spotLights[" + std::to_string(index) + "].cutOff", _cutOff);
	shaderProgram->setFloat("spotLights[" + std::to_string(index) + "].outerCutOff", _outerCutOff);
}

void SpotLight::setPosition(math::Vec3 pos) {
	_position = pos;
}

void SpotLight::setDirection(math::Vec3 dir) {
	_direction = dir;
}

void SpotLight::setAmbientColor(shading::Color col) {
	_ambient = col;
}

void SpotLight::setDiffuseColor(shading::Color col) {
	_diffuse = col;
}

void SpotLight::setSpecularColor(shading::Color col) {
	_specular = col;
}

void SpotLight::setConstant(float c) {
	_constant = c;
}

void SpotLight::setLinearConstant(float c) {
	_linearConstant = c;
}

void SpotLight::setQuadraticConstant(float c) {
	_quadraticConstant = c;
}

void SpotLight::setCutOff(float c) {
	_cutOff = c;
}

void SpotLight::setOuterCutOff(float c) {
	_outerCutOff = c;
}

Light::LightType SpotLight::type() const {
	return LightType::SpotLight;
}