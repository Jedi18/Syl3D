#pragma once

#include <string>
#include <vector>
#include <map>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../shaderprogram.h"
#include "../shadermanager.h"

class TextureMaterial
{
public:
	TextureMaterial(std::string shaderName = "default");

	void addTexture(std::string textureName, std::string textureFile, bool flipVertical = false);

	void setShaderProgramName(std::string shaderName);

	std::string shaderName() const;

	void activateTextures();

	unsigned int getTextureId(int index) const;

	unsigned int ID() const;

private:
	unsigned int _ID;
	std::string _shaderName;
	ShaderManager* shaderManager;
	std::vector<unsigned int> _textures;
	std::vector<std::string> _textureNames;

	static const std::map<int, GLenum> texturePositionMap;
};