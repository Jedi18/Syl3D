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

void ShaderProgram::setBool(std::string uniformName, bool val) {
	glUniform1i(glGetUniformLocation(_ID, uniformName.c_str()), val);
}

void ShaderProgram::setFloat(std::string uniformName, float val) {
	glUniform1f(glGetUniformLocation(_ID, uniformName.c_str()), val);
}

void ShaderProgram::setInt(std::string uniformName, int val) {
	glUniform1i(glGetUniformLocation(_ID, uniformName.c_str()), val);
}

void ShaderProgram::setVec3(std::string uniformName, math::Vec3 val) {
	glUniform3f(glGetUniformLocation(_ID, uniformName.c_str()), val.x, val.y, val.z);
}

void ShaderProgram::setColor(std::string uniformName, shading::Color val) {
	glUniform4f(glGetUniformLocation(_ID, uniformName.c_str()), val.r, val.g, val.b, val.a);
}

void ShaderProgram::setMat4(std::string uniformName, glm::mat4 val) {
	glUniformMatrix4fv(glGetUniformLocation(_ID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}