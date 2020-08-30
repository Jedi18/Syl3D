#pragma once

#include <string>
#include "shaderprogram.h"

class Shader
{
public:
	enum class ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER
	};

public:
	Shader();

	ShaderProgram createShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	unsigned int createShader(const std::string& vertexShaderPath, ShaderType shaderType);

	void checkShaderCompileError(unsigned int shader, ShaderType shaderType);

	void checkProgramLinkError(unsigned int program);
};