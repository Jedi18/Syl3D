#include "renderer.h"
#include "mesh/rectangle.h"
#include "mesh/coloredtriangle.h"
#include "mesh/triangle.h"
#include "mesh/texturedrectangle.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>

Renderer::Renderer() 
	:
	_shaderProgram(-1),
	_texMaterial(&_shaderProgram)
{}

void Renderer::initialize() {
	_shaderProgram = _shader.createShaderProgram("texvertex.shader", "texfragment.shader");

	//mesh::Rectangle rectangle;
	mesh::Rectangle meshObject;

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, meshObject.numVertices(), meshObject.vertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshObject.numIndices(), meshObject.indices(), GL_STATIC_DRAW);

	// triangle - glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);

	std::vector<mesh::VertexAttributeData> vertexAttribs = meshObject.vertexAttributes();
	for (int i = 0; i < vertexAttribs.size(); i++) {
		glVertexAttribPointer(i, vertexAttribs[i].size, GL_FLOAT, GL_FALSE, vertexAttribs[i].stride, (void*)vertexAttribs[i].pointer);
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	_VAO = VAO;

	_texMaterial.addTexture("container.jpg");
	_texMaterial.addTexture("awesomeface.png", true, true);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shaderProgram.use();
	_texMaterial.activateTextures();
	_shaderProgram.setFloat("visibility", vis);

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rectangle
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //triangle
}