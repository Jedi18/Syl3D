#include "object.h"

#include "../entity/entityfactory.h"

Object::Object() 
	:
	_ID(EntityFactory::generateID()),
	_scale(1, 1, 1)
{
	_rotation = glm::mat4(1.0f);
}

Object::Object(math::Vec3 position)
	:
	Object()
{
	_pos = position;
}

glm::mat4 Object::modelMatrix() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(_pos.x, _pos.y, _pos.z));
	model *= _rotation;
	model = glm::scale(model, glm::vec3(_scale.x, _scale.y, _scale.z));
	return model;
}

void Object::translate(math::Vec3 pos) {
	_pos += pos;
}

void Object::translateTo(math::Vec3 pos) {
	_pos = pos;
}

void Object::rotateX(float angleInRadians) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(1, 0, 0));
}

void Object::rotateY(float angleInRadians) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(0, 1, 0));
}

void Object::rotateZ(float angleInRadians) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(0, 0, 1));
}

void Object::rotateAround(float angleInRadians, math::Vec3 axis) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(axis.x, axis.y, axis.z));
}

void Object::rotateTo(float angleInRadians, math::Vec3 axis) {
	_rotation = glm::rotate(glm::mat4(1.0f), angleInRadians, glm::vec3(axis.x, axis.y, axis.z));
}

glm::mat4 Object::rotation() const {
	return _rotation;
}

void Object::setRotation(glm::mat4 rot) {
	_rotation = rot;
}

void Object::scale(math::Vec3 scaleVec) {
	_scale.x *= scaleVec.x;
	_scale.y *= scaleVec.y;
	_scale.z *= scaleVec.z;
}

void Object::scaleX(float xfactor) {
	_scale.x *= xfactor;
}

void Object::scaleY(float yfactor) {
	_scale.y *= yfactor;
}

void Object::scaleZ(float zfactor) {
	_scale.z *= zfactor;
}

void Object::setScale(math::Vec3 scaleVec) {
	_scale = scaleVec;
}

void Object::scale(float factor) {
	_scale *= factor;
}

math::Vec3 Object::position() const {
	return _pos;
}

math::Vec3 Object::getScale() const {
	return _scale;
}

unsigned int Object::id() const {
	return _ID;
}