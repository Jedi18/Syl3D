#pragma once

#include <string>
#include <vector>
#include <map>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "shaderprogram.h"

class TextureMaterial
{
public:
	TextureMaterial(ShaderProgram* shaderProgram);

	void addTexture(std::string textureFile, bool rgba = false, bool flipVertical = false);

	void setShaderProgram(ShaderProgram* shaderProgram);

	void activateTextures();

private:
	ShaderProgram* _shaderProgram;
	std::vector<unsigned int> _textures;

	static const std::map<int, GLenum> texturePositionMap;
};