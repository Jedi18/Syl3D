#pragma once

#include <string>
#include <vector>
#include <map>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../shaderprogram.h"

class TextureMaterial
{
public:
	TextureMaterial(std::shared_ptr<ShaderProgram> shaderProgram);

	void addTexture(std::string textureName, std::string textureFile, bool flipVertical = false);

	void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	void activateTextures();

private:
	std::shared_ptr<ShaderProgram> _shaderProgram;
	std::vector<unsigned int> _textures;
	std::vector<std::string> _textureNames;

	static const std::map<int, GLenum> texturePositionMap;
};