#include "directionallight.h"

using namespace light;

DirectionalLight::DirectionalLight(math::Vec3 direction, shading::Color diffuse)
	:
	_direction(direction.normalized()),
	_diffuse(diffuse),
	_ambient(0.05f, 0.05f, 0.05f),
	_specular(shading::Color(1.0f, 1.0f, 1.0f))
{}

void DirectionalLight::setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) {
	shaderProgram->setVec3("dirLights[" + std::to_string(index) + "].direction", _direction);
	shaderProgram->setColor3("dirLights[" + std::to_string(index) + "].ambient", _ambient);
	shaderProgram->setColor3("dirLights[" + std::to_string(index) + "].diffuse", _diffuse);
	shaderProgram->setColor3("dirLights[" + std::to_string(index) + "].specular", _specular);
}

void DirectionalLight::setDirection(math::Vec3 dir) {
	_direction = dir.normalized();
}

void DirectionalLight::setAmbientColor(shading::Color col) {
	_ambient = col;
}

void DirectionalLight::setDiffuseColor(shading::Color col) {
	_diffuse = col;
}

void DirectionalLight::setSpecularColor(shading::Color col) {
	_specular = col;
}

Light::LightType DirectionalLight::type() const {
	return LightType::Directional;
}