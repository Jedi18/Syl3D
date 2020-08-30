#include "shaderprogram.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

ShaderProgram::ShaderProgram(unsigned int ID) 
	:
	_ID(ID)
{}

void ShaderProgram::use() {
	glUseProgram(_ID);
}

unsigned int ShaderProgram::id() const {
	return _ID;
}

void ShaderProgram::setBool(const std::string& uniformName, bool val) {
	glUniform1i(glGetUniformLocation(_ID, uniformName.c_str()), val);
}

void ShaderProgram::setFloat(const std::string& uniformName, float val) {
	glUniform1f(glGetUniformLocation(_ID, uniformName.c_str()), val);
}

void ShaderProgram::setInt(const std::string& uniformName, int val) {
	glUniform1i(glGetUniformLocation(_ID, uniformName.c_str()), val);
}

void ShaderProgram::setVec3(const std::string& uniformName, math::Vec3 val) {
	glUniform3f(glGetUniformLocation(_ID, uniformName.c_str()), val.x, val.y, val.z);
}

void ShaderProgram::setColor(const std::string& uniformName, shading::Color val) {
	glUniform4f(glGetUniformLocation(_ID, uniformName.c_str()), val.r, val.g, val.b, val.a);
}