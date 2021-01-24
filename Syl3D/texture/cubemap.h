#pragma once

#include <string>
#include <vector>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class CubeMap
{
public:
	CubeMap(std::string cubemapFolderPath, std::string shaderName = "skyboxShader");

	void activateCubemap();

	std::string shaderName() const;

	unsigned int id() const;

private:
	unsigned int _ID;
	std::string _shaderName;
};

