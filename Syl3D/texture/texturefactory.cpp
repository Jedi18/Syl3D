#include "texturefactory.h"

TextureFactory* TextureFactory::_textureFactory = nullptr;
std::vector<std::string> TextureFactory::shaderList = std::vector<std::string>();
std::shared_ptr<ShaderManager> TextureFactory::shaderManager = nullptr;
std::map<std::string, std::shared_ptr<TextureMaterial>> TextureFactory::textureList = std::map<std::string, std::shared_ptr<TextureMaterial>>();

TextureFactory* TextureFactory::textureFactory() {
	if (_textureFactory == nullptr) {
		_textureFactory = new TextureFactory();
	}

	return _textureFactory;
}

void TextureFactory::addShader(const std::string& shaderName) {
	shaderList.push_back(shaderName);
}

void TextureFactory::setShaderManager(std::shared_ptr<ShaderManager> shaderManager) {
	TextureFactory::shaderManager = shaderManager;
}

std::shared_ptr<TextureMaterial> TextureFactory::addTextureMaterial(const std::string& textureName, const std::string& diffuseTex,
	const std::string& specularTex, std::string shaderName) {
	if (shaderName == "default") {
		shaderName = shaderList[0];
	}

	std::shared_ptr<TextureMaterial> _texMaterial = std::make_shared<TextureMaterial>(shaderManager->shaderByName(shaderName));
	_texMaterial->addTexture("material.diffuse", diffuseTex);
	_texMaterial->addTexture("material.specular", specularTex);
	textureList[textureName] = _texMaterial;
	return _texMaterial;
}