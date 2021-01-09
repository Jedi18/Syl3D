#include "texturematerial.h"
#include "texturefactory.h"

#include "../vendor/stb_image/stb_image.h"

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

TextureMaterial::TextureMaterial(std::string shaderName)
	:
	_ID(TextureFactory::generateID()),
	_shaderName(shaderName),
	shaderManager(ShaderManager::shaderManager())
{}

unsigned int TextureMaterial::ID() const {
	return _ID;
}

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
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

	shaderManager->useShader(_shaderName);
	glActiveTexture(texturePositionMap.at(_textures.size()));
	glBindTexture(GL_TEXTURE_2D, texture1);

	shaderManager->shaderByName(_shaderName)->setInt(textureName, _textures.size());
	_textures.push_back(texture1);
	_textureNames.push_back(textureName);
}

void TextureMaterial::setShaderProgramName(std::string shaderName) {
	_shaderName = shaderName;
}

std::string TextureMaterial::shaderName() const {
	return _shaderName;
}

void TextureMaterial::activateTextures() {
	shaderManager->useShader(_shaderName);
	for (int i = 0; i < _textures.size(); i++) {
		glActiveTexture(texturePositionMap.at(i));
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		shaderManager->shaderByName(_shaderName)->setInt(_textureNames[i], i);
	}
}

unsigned int TextureMaterial::getTextureId(int index) const {
	return _textures[index];
}