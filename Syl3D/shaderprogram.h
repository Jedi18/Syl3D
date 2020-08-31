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

	void setBool(std::string uniformName, bool val);

	void setFloat(std::string uniformName, float val);

	void setInt(std::string uniformName, int val);

	void setVec3(std::string uniformName, math::Vec3 val);

	void setColor(std::string uniformName, shading::Color val);

private:
	unsigned int _ID;
};