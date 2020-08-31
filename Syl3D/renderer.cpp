#include "renderer.h"
#include "mesh/rectanglemesh.h"
#include "mesh/coloredtriangle.h"
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
	_shaderProgram = _shader.createShaderProgram("shaders/texvertex.shader", "shaders/texfragment.shader");

	_rectangle = new entity::Rectangle();
	_triangle = new entity::Triangle();

	_texMaterial.addTexture("container.jpg");
	_texMaterial.addTexture("awesomeface.png", true, true);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shaderProgram.use();
	_texMaterial.activateTextures();
	_shaderProgram.setFloat("visibility", vis);

	_rectangle->draw();
	//_triangle->draw();
}