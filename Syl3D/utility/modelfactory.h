#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../entity/model.h"

namespace utility
{
	class ModelFactory
	{
	public:
		static entity::Model loadModel(std::string path);

	private:
		static void processNode(aiNode* node, const aiScene* scene, std::vector<mesh::ModelMesh>& meshes);
		static mesh::ModelMesh processMesh(aiMesh* mesh, const aiScene* scene);

		static std::vector<float> convertVertexesToFloatVector(const std::vector<mesh::Vertex>& vertexes);
	};
}