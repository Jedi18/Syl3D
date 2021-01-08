#include "entity.h"

#include "entityfactory.h"

using namespace entity;

Entity::Entity()
	:
	_textureMaterial(nullptr),
	_usesEBO(false)
{
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