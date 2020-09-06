#pragma once

#include <map>
#include <string>
#include <memory>

#include "shader.h"
#include "shaderprogram.h"

class ShaderManager
{
public:
	ShaderManager();

	void initialize();

	void addShader(std::string shaderName, std::string vertexShaderPath, std::string fragmentShaderPath);

	std::shared_ptr<ShaderProgram> shaderByName(std::string shaderName);

	std::shared_ptr<ShaderProgram> currentShader();

	void useShader(std::string shaderName);

private:
	Shader _shader;
	std::map<std::string, std::shared_ptr<ShaderProgram>> _shaderPrograms;
	std::string _currentShader;
};