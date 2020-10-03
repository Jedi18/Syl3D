#include "model.h"

using namespace entity;

Model::Model(std::string shaderName) 
	:
	Entity(shaderName)
{}

Model::Model(const std::vector<mesh::ModelMesh>& meshes, std::string shaderName = "default")
	:
	Model(shaderName)
{
	_meshes = meshes;
}

void Model::draw() {

}