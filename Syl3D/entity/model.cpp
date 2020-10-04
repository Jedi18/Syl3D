#include "model.h"

using namespace entity;

Model::Model(const std::vector<std::shared_ptr<mesh::ModelMesh>>& meshes, std::string shaderName)
	:
	Entity(shaderName),
	_meshes(meshes)
{
	size_t n = _meshes.size();
	std::vector<std::shared_ptr<mesh::Mesh>> arr(n);

	for (int i = 0; i < n; i++) {
		arr[i] = std::static_pointer_cast<mesh::Mesh>(_meshes[i]);
	}

	this->initialize(arr);
}

void Model::draw() {
	if (_usesEBO) {
		int n = _meshes.size();

		for (int i = 0; i < n; i++) {
			glBindVertexArray(_VAOs[i]);
			glDrawElements(GL_TRIANGLES, _meshes[i]->numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		}
	}
}