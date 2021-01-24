#pragma once

#include "../mesh/skyboxmesh.h"
#include "../texture/cubemap.h"

class Skybox
{
public:
	Skybox();

	void draw();

	void setCubemap(std::shared_ptr<CubeMap> cubeMap);

	std::shared_ptr<CubeMap> cubemap();

	void activateCubemap();

private:
	unsigned int _VAO;
	std::shared_ptr<CubeMap> _cubemap;
	std::shared_ptr<mesh::SkyboxMesh> _skyboxMesh;
};

