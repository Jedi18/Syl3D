#pragma once

#include <string>
#include "vec3.h"
#include "color.h"

class ShaderProgram
{
public:
	ShaderProgram(unsigned int ID);

	void use();

	unsigned int id() const;

	void setBool(const std::string& uniformName, bool val);

	void setFloat(const std::string& uniformName, float val);

	void setInt(const std::string& uniformName, int val);

	void setVec3(const std::string& uniformName, math::Vec3 val);

	void setColor(const std::string& uniformName, shading::Color val);

private:
	unsigned int _ID;
};