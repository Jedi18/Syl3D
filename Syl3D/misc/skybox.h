#pragma once

#include "../mesh/skyboxmesh.h"
#include "../texture/cubemap.h"

/**
* Skybox class, holds the VAO for the skybox mesh and  cubemap for the skybox
*/
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

