#include "texturematerial.h"

#include "stb_image.h"

#include <iostream>

const std::map<int, GLenum> TextureMaterial::texturePositionMap = {
	{0, GL_TEXTURE0},
	{1, GL_TEXTURE1},
	{2, GL_TEXTURE2},
	{3, GL_TEXTURE3},
	{4, GL_TEXTURE4},
	{5, GL_TEXTURE5},
	{6, GL_TEXTURE6},
	{7, GL_TEXTURE7}
};

TextureMaterial::TextureMaterial(std::shared_ptr<ShaderProgram> shaderProgram)
	:
	_shaderProgram(shaderProgram)
{}

void TextureMaterial::addTexture(std::string textureName, std::string textureFile, bool flipVertical) {
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (flipVertical) {
		stbi_set_flip_vertically_on_load(true);
	}
	else {
		stbi_set_flip_vertically_on_load(false);
	}

	int width, height, nrChannels = 4;
	unsigned char* data = stbi_load(textureFile.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		if (nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else {
		std::cout << "Failed to load the texture" << std::endl;
	}

	stbi_image_free(data);

	_shaderProgram->use();
	glActiveTexture(texturePositionMap.at(_textures.size()));
	glBindTexture(GL_TEXTURE_2D, texture1);

	_shaderProgram->setInt(textureName, _textures.size());
	_textures.push_back(texture1);
	_textureNames.push_back(textureName);
}

void TextureMaterial::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
	_shaderProgram = shaderProgram;
}

void TextureMaterial::activateTextures() {
	_shaderProgram->use();
	for (int i = 0; i < _textures.size(); i++) {
		glActiveTexture(texturePositionMap.at(i));
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		_shaderProgram->setInt(_textureNames[i], i);
	}
}