#pragma once

#include <vector>
#include <sstream>
#include <map>
#include "../shadermanager.h"
#include "texturematerial.h"

class TextureFactory
{
public:
	static TextureFactory* textureFactory();

	static void addShader(const std::string& shaderName);

	static std::shared_ptr<TextureMaterial> addTextureMaterial(const std::string& textureName, const std::string& diffuseTex, const std::string& specularTex, std::string shaderName = "default");

	static std::shared_ptr<TextureMaterial> getTextureMaterial(const std::string& textureName);

	static std::vector<std::string> getAvailableTextureMaterials();

	static std::string getTextureMaterialName(std::shared_ptr<TextureMaterial>);

	static void releaseInstance();

	static unsigned int generateID();

private:
	static unsigned int TEXTURE_COUNT;

	static TextureFactory* _textureFactory;
	static std::vector<std::string> shaderList;
	static ShaderManager* shaderManager;
	static std::map<std::string, std::shared_ptr<TextureMaterial>> textureList;
};

