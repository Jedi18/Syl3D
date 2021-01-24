#include "skybox.h"

Skybox::Skybox() 
	:
	_skyboxMesh(std::make_shared<mesh::SkyboxMesh>())
{
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &_VAO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _skyboxMesh->numVertices(), _skyboxMesh->vertices(), GL_STATIC_DRAW);

	std::vector<mesh::VertexAttributeData> vertexAttribs = _skyboxMesh->vertexAttributes();
	for (int i = 0; i < vertexAttribs.size(); i++) {
		glVertexAttribPointer(i, vertexAttribs[i].size, GL_FLOAT, GL_FALSE, vertexAttribs[i].stride, (void*)vertexAttribs[i].pointer);
		glEnableVertexAttribArray(i);
	}
}

void Skybox::draw() {
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Skybox::setCubemap(std::shared_ptr<CubeMap> cubeMap) {
	_cubemap = cubeMap;
}

std::shared_ptr<CubeMap> Skybox::cubemap() {
	return _cubemap;
}

void Skybox::activateCubemap() {
	if (_cubemap != nullptr) {
		_cubemap->activateCubemap();
	}
}