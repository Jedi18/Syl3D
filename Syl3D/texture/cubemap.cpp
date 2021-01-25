#include "cubemap.h"

#include <iostream>
#include "../vendor/stb_image/stb_image.h"
#include "../shadermanager.h"

CubeMap::CubeMap(std::string cubemapFolderPath, std::string shaderName) {
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);
	_shaderName = shaderName;

	std::vector<std::string> faces = {
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"back.png",
		"front.png"
	};

	ShaderManager* shaderManager = ShaderManager::shaderManager();

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load((cubemapFolderPath + "/" + faces[i]).c_str(), &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			std::cout << "Could not load cubemap : " << cubemapFolderPath << '\n';
		}
		stbi_image_free(data);
	}

	shaderManager->shaderByName(shaderName)->setInt("skybox", 0);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

std::string CubeMap::shaderName() const {
	return _shaderName;
}

void CubeMap::activateCubemap() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);
}

unsigned int CubeMap::id() const {
	return _ID;
}