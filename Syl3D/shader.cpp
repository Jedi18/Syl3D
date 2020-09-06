#include "shader.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {}

std::shared_ptr<ShaderProgram> Shader::createShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	GLuint vertexShader = createShader(vertexShaderPath, ShaderType::VERTEX_SHADER);
	GLuint fragmentShader = createShader(fragmentShaderPath, ShaderType::FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	checkProgramLinkError(shaderProgram);

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return std::make_shared<ShaderProgram>(shaderProgram);
}

unsigned int Shader::createShader(const std::string& vertexShaderPath, ShaderType shaderType) {
	const char* shaderSource;

	std::ifstream shaderFile(vertexShaderPath);
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	shaderFile.close();

	std::string bufferString = buffer.str();
	shaderSource = bufferString.c_str();

	GLenum shadert;
	if (shaderType == ShaderType::VERTEX_SHADER) {
		shadert = GL_VERTEX_SHADER;
	}
	else {
		shadert = GL_FRAGMENT_SHADER;
	}

	GLuint shader = glCreateShader(shadert);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	checkShaderCompileError(shader, shaderType);
	return shader;
}

void Shader::checkShaderCompileError(unsigned int shader, ShaderType shaderType) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR: Shader " << ((shaderType==ShaderType::VERTEX_SHADER) ? ("Vertex") : ("Fragment")) << " Compilation Failed - " << infoLog << '\n';
	}
}

void Shader::checkProgramLinkError(unsigned int program) {
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR: Shader Program Linking Failed - " << infoLog << '\n';
	}
}