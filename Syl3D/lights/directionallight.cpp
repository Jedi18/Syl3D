#include "directionallight.h"

using namespace light;

DirectionalLight::DirectionalLight(math::Vec3 direction, shading::Color diffuse)
	:
	Light(math::Vec3(0.0f, 0.0f, 0.0f), diffuse),
	_direction(direction.normalized())
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

const math::Vec3 DirectionalLight::direction() const {
	return _direction;
}

Light::LightType DirectionalLight::type() const {
	return LightType::Directional;
}

void DirectionalLight::accept(LightVisitor& v) {
	v.visit(this);
}