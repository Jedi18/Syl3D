#pragma once

#include <string>

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

	unsigned int createShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	unsigned int createShader(const std::string& vertexShaderPath, ShaderType shaderType);

	void checkShaderCompileError(unsigned int shader, ShaderType shaderType);

	void checkProgramLinkError(unsigned int program);
};