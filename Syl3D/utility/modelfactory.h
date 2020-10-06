#pragma once

#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../entity/model.h"
#include "../shaderprogram.h"

namespace utility
{
	class ModelFactory
	{
	private:
		struct TexturePath
		{
			std::string type;
			std::string path;
		};

	public:
		static std::shared_ptr<entity::Model> loadModel(const std::string& path, const std::string& shaderName, std::shared_ptr<ShaderProgram> shaderProgram);

	private:
		static void processNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<mesh::ModelMesh>>& meshes);

		static std::shared_ptr<mesh::ModelMesh> processMesh(aiMesh* mesh, const aiScene* scene);

		static std::vector<float> convertVertexesToFloatVector(const std::vector<mesh::Vertex>& vertexes);

		static std::vector<TexturePath> loadMaterialTexture(aiMaterial* material, aiTextureType type, const std::string& typeName);

	private:
		static std::map<std::string, TexturePath> textures;
	};
}