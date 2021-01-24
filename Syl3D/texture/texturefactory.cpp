#include "texturefactory.h"

#include <unordered_map>
#include "../utility/fileio.h"

unsigned int TextureFactory::TEXTURE_COUNT = 0;
TextureFactory* TextureFactory::_textureFactory = nullptr;
std::vector<std::string> TextureFactory::shaderList = std::vector<std::string>();
ShaderManager* TextureFactory::shaderManager = nullptr;
std::map<std::string, std::shared_ptr<TextureMaterial>> TextureFactory::textureList = std::map<std::string, std::shared_ptr<TextureMaterial>>();

TextureFactory* TextureFactory::textureFactory() {
	if (_textureFactory == nullptr) {
		TextureFactory::shaderManager = ShaderManager::shaderManager();
		_textureFactory = new TextureFactory();
	}

	return _textureFactory;
}

void TextureFactory::addShader(const std::string& shaderName) {
	shaderList.push_back(shaderName);
}

std::shared_ptr<TextureMaterial> TextureFactory::addTextureMaterial(const std::string& textureName, const std::string& diffuseTex,
	const std::string& specularTex, std::string shaderName) {
	if (shaderName == "default") {
		shaderName = shaderList[0];
	}

	std::shared_ptr<TextureMaterial> _texMaterial = std::make_shared<TextureMaterial>(shaderName);
	_texMaterial->addTexture("material.diffuse", diffuseTex);
	_texMaterial->addTexture("material.specular", specularTex);
	textureList[textureName] = _texMaterial;
	return _texMaterial;
}

std::shared_ptr<TextureMaterial> TextureFactory::getTextureMaterial(const std::string& textureName) {
	return textureList[textureName];
}

std::vector<std::string> TextureFactory::getAvailableTextureMaterials() {
	std::vector<std::string> textureMaterials;

	for (auto iter = textureList.begin(); iter != textureList.end(); iter++) {
		textureMaterials.push_back((*iter).first);
	}

	return textureMaterials;
}

std::string TextureFactory::getTextureMaterialName(std::shared_ptr<TextureMaterial> textureMaterial) {
	for (auto iter = textureList.begin(); iter != textureList.end(); iter++) {
		if ((*iter).second->ID() == textureMaterial->ID()) {
			return (*iter).first;
		}
	}

	return "";
}

unsigned int TextureFactory::generateID() {
	TEXTURE_COUNT++;
	return TEXTURE_COUNT;
}

void TextureFactory::releaseInstance() {
	if (_textureFactory != nullptr) {
		delete _textureFactory;
	}
}

void TextureFactory::addTexturesFromFolder(const std::string& folderName) {
	std::vector<std::string> filesInFolder = utility::FileIO::filesInPath(folderName);
	std::unordered_map<std::string, std::string> texturesFoundDiffuse;
	std::unordered_map<std::string, std::string> texturesFoundSpecular;

	for (const std::string& file : filesInFolder) {
		size_t index = file.find_last_of('_');
		size_t dotindex = file.find_last_of('.');
		std::string textureName = file.substr(0, index);
		std::string type = file.substr(index + 1, dotindex - index - 1);
		
		if (type == "diffuse") {
			texturesFoundDiffuse[textureName] = file;
		}

		if (type == "specular") {
			texturesFoundSpecular[textureName] = file;
		}
	}

	for (auto diffuseTexture : texturesFoundDiffuse) {
		if (texturesFoundSpecular.find(diffuseTexture.first) != texturesFoundSpecular.end()) {
			addTextureMaterial(diffuseTexture.first, folderName + "/" + diffuseTexture.second, folderName + "/" + texturesFoundSpecular[diffuseTexture.first]);
		}
		else {
			addTextureMaterial(diffuseTexture.first, folderName + "/" + diffuseTexture.second, folderName + "/" + "default_specular.jpg");
		}
	}
}