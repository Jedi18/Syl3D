#pragma once

#include <vector>
#include <map>
#include "../shadermanager.h"
#include "texturematerial.h"

class TextureFactory
{
public:
	static TextureFactory* textureFactory();

	static void addShader(const std::string& shaderName);

	static void setShaderManager(std::shared_ptr<ShaderManager> shaderManager);

	static std::shared_ptr<TextureMaterial> addTextureMaterial(const std::string& textureName, const std::string& diffuseTex, const std::string& specularTex, std::string shaderName = "default");

	static std::shared_ptr<TextureMaterial> getTextureMaterial(const std::string& textureName);

	static void releaseInstance();

private:
	static TextureFactory* _textureFactory;
	static std::vector<std::string> shaderList;
	static std::shared_ptr<ShaderManager> shaderManager;
	static std::map<std::string, std::shared_ptr<TextureMaterial>> textureList;
};

