#include "entity.h"

using namespace entity;

void Entity::initialize(mesh::Mesh* meshObject) {
	if (meshObject->indices() == nullptr) {
		_usesEBO = false;
	}
	else {
		_usesEBO = true;
	}

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

	_VAO = VAO;
}