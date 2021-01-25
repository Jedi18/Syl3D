#pragma once

#include <string>
#include <vector>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

/**
* Cubemap class (for skybox, etc.)
*/
class CubeMap
{
public:
	/**
	* Loads cubemap textures stored in given folder path
	* Given folder path should contain files named top.png, bottom.png etc.
	*/
	CubeMap(std::string cubemapFolderPath, std::string shaderName = "skyboxShader");

	void activateCubemap();

	std::string shaderName() const;

	unsigned int id() const;

private:
	unsigned int _ID;
	std::string _shaderName;
};

