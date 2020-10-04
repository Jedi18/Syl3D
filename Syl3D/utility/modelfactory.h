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
		static std::shared_ptr<entity::Model> loadModel(const std::string& path, const std::string& shaderName);

	private:
		static void processNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<mesh::ModelMesh>>& meshes);
		static std::shared_ptr<mesh::ModelMesh> processMesh(aiMesh* mesh, const aiScene* scene);

		static std::vector<float> convertVertexesToFloatVector(const std::vector<mesh::Vertex>& vertexes);
	};
}