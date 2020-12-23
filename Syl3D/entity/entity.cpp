#include "entity.h"

#include "entityfactory.h"

using namespace entity;

Entity::Entity(std::string shaderName)
	:
	_ID(EntityFactory::generateID()),
	_shaderName(shaderName),
	_scale(1,1,1),
	_textureMaterial(nullptr),
	_usesEBO(false)
{
	_rotation = glm::mat4(1.0f);
}

void Entity::initialize(const std::vector<std::shared_ptr<mesh::Mesh>>& meshObjects) {
	if (meshObjects[0]->indices() == nullptr) {
		_usesEBO = false;
	}
	else {
		_usesEBO = true;
	}

	for (std::shared_ptr<mesh::Mesh> meshObject : meshObjects) {
		GLuint VBO;
		glGenBuffers(1, &VBO);

		GLuint EBO;
		if (_usesEBO) {
			glGenBuffers(1, &EBO);
		}

		GLuint VAO;
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, meshObject->numVertices(), meshObject->vertices(), GL_STATIC_DRAW);

		if (_usesEBO) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshObject->numIndices(), meshObject->indices(), GL_STATIC_DRAW);
		}

		std::vector<mesh::VertexAttributeData> vertexAttribs = meshObject->vertexAttributes();
		for (int i = 0; i < vertexAttribs.size(); i++) {
			glVertexAttribPointer(i, vertexAttribs[i].size, GL_FLOAT, GL_FALSE, vertexAttribs[i].stride, (void*)vertexAttribs[i].pointer);
			glEnableVertexAttribArray(i);
		}

		_VAOs.push_back(VAO);
	}
}

glm::mat4 Entity::modelMatrix() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(_pos.x, _pos.y, _pos.z));
	model *= _rotation;
	model = glm::scale(model, glm::vec3(_scale.x, _scale.y, _scale.z));
	return model;
}

void Entity::translate(math::Vec3 pos) {
	_pos += pos;
}

void Entity::translateTo(math::Vec3 pos) {
	_pos = pos;
}

void Entity::rotateX(float angleInRadians) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(1, 0, 0));
}

void Entity::rotateY(float angleInRadians) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(0, 1, 0));
}

void Entity::rotateZ(float angleInRadians) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(0, 0, 1));
}

void Entity::rotateAround(float angleInRadians, math::Vec3 axis) {
	_rotation = glm::rotate(_rotation, angleInRadians, glm::vec3(axis.x, axis.y, axis.z));
}

void Entity::rotateTo(float angleInRadians, math::Vec3 axis) {
	_rotation = glm::rotate(glm::mat4(1.0f), angleInRadians, glm::vec3(axis.x, axis.y, axis.z));
}

glm::mat4 Entity::rotation() const {
	return _rotation;
}

void Entity::setRotation(glm::mat4 rot) {
	_rotation = rot;
}

void Entity::scale(math::Vec3 scaleVec) {
	_scale.x *= scaleVec.x;
	_scale.y *= scaleVec.y;
	_scale.z *= scaleVec.z;
}

void Entity::scaleX(float xfactor) {
	_scale.x *= xfactor;
}

void Entity::scaleY(float yfactor) {
	_scale.y *= yfactor;
}

void Entity::scaleZ(float zfactor) {
	_scale.z *= zfactor;
}

void Entity::setScale(math::Vec3 scaleVec) {
	_scale = scaleVec;
}

void Entity::scale(float factor) {
	_scale *= factor;
}

math::Vec3 Entity::position() const {
	return _pos;
}

math::Vec3 Entity::getScale() const {
	return _scale;
}

std::string Entity::shaderName() const {
	return _shaderName;
}

unsigned int Entity::id() const {
	return _ID;
}

void Entity::setTexture(std::shared_ptr<TextureMaterial> texMaterial) {
	_textureMaterial = texMaterial;
}

std::shared_ptr<TextureMaterial> Entity::texture() {
	return _textureMaterial;
}

void Entity::activateTexture() {
	if (_textureMaterial != nullptr) {
		_textureMaterial->activateTextures();
	}
}