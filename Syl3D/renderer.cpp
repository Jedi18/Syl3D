#include "renderer.h"
#include "rectangle.h"
#include "coloredtriangle.h"
#include "triangle.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

Renderer::Renderer() 
	:
	_shaderProgram(-1)
{}

void Renderer::initialize() {
	_shaderProgram = _shader.createShaderProgram("vertex.shader", "fragment.shader");

	//mesh::Rectangle rectangle;
	mesh::ColoredTriangle coloredTriangle;

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, coloredTriangle.numVertices(), coloredTriangle.vertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, coloredTriangle.numIndices(), coloredTriangle.indices(), GL_STATIC_DRAW);

	// triangle - glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);

	std::vector<mesh::VertexAttributeData> vertexAttribs = coloredTriangle.vertexAttributes();
	for (int i = 0; i < vertexAttribs.size(); i++) {
		glVertexAttribPointer(i, vertexAttribs[i].size, GL_FLOAT, GL_FALSE, vertexAttribs[i].stride, (void*)vertexAttribs[i].pointer);
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	_VAO = VAO;
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/*float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};*/

	/*float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	_shaderProgram.use();
	_shaderProgram.setColor("ourColor", shading::Color(0.0f, greenValue, 0.0f));*/
	_shaderProgram.use();

	glBindVertexArray(_VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); -- rectangle
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}