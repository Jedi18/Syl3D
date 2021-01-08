#include "pointlight.h"

using namespace light;

PointLight::PointLight(math::Vec3 position, shading::Color diffuse)
	:
	Light(position),
	_diffuse(diffuse),
	_ambient(0.05f, 0.05f, 0.05f),
	_specular(shading::Color(1.0f, 1.0f, 1.0f)),
	_constant(1.0f),
	_linearConstant(0.09f),
	_quadraticConstant(0.032f)
{}

void PointLight::setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) {
	shaderProgram->setVec3("pointLights[" + std::to_string(index) + "].position", _pos);
	shaderProgram->setColor3("pointLights[" + std::to_string(index) + "].ambient", _ambient);
	shaderProgram->setColor3("pointLights[" + std::to_string(index) + "].diffuse", _diffuse);
	shaderProgram->setColor3("pointLights[" + std::to_string(index) + "].specular", _specular);
	shaderProgram->setFloat("pointLights[" + std::to_string(index) + "].constant", _constant);
	shaderProgram->setFloat("pointLights[" + std::to_string(index) + "].linearConstant", _linearConstant);
	shaderProgram->setFloat("pointLights[" + std::to_string(index) + "].quadraticConstant", _quadraticConstant);
}

void PointLight::setAmbientColor(shading::Color col) {
	_ambient = col;
}

void PointLight::setDiffuseColor(shading::Color col) {
	_diffuse = col;
}

void PointLight::setSpecularColor(shading::Color col) {
	_specular = col;
}

void PointLight::setConstant(float c) {
	_constant = c;
}

void PointLight::setLinearConstant(float c) {
	_linearConstant = c;
}

void PointLight::setQuadraticConstant(float c) {
	_quadraticConstant = c;
}

Light::LightType PointLight::type() const {
	return LightType::Point;
}