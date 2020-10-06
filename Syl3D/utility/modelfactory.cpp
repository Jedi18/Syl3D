#include "modelfactory.h"

using namespace utility;

std::map<std::string, ModelFactory::TexturePath> ModelFactory::textures;

std::shared_ptr<entity::Model> ModelFactory::loadModel(const std::string& path, const std::string& shaderName, std::shared_ptr<ShaderProgram> shaderProgram) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp loading error" << importer.GetErrorString() << std::endl;
		throw std::exception("Assimp Loading Error");
	}

	textures.clear();
	std::vector<std::shared_ptr<mesh::ModelMesh>> meshes;
	std::string directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene, meshes);

	std::shared_ptr<TextureMaterial> _modelTex = std::make_shared<TextureMaterial>(shaderProgram);
	for (auto texture : textures) {
		if (texture.second.type == "texture_diffuse") {
			_modelTex->addTexture("material.diffuse", directory + "/" + texture.first);
		}

		if (texture.second.type == "texture_specular") {
			_modelTex->addTexture("material.specular", directory + "/" + texture.first);
		}
	}

	std::shared_ptr<entity::Model> model = std::make_shared<entity::Model>(meshes, shaderName);
	model->setTexture(_modelTex);
	return model;
}

void ModelFactory::processNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<mesh::ModelMesh>>& meshes) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, meshes);
	}
}

std::shared_ptr<mesh::ModelMesh> ModelFactory::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<unsigned int> indices;
	std::vector<mesh::Vertex> vertices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		mesh::Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			vertex.textureCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.textureCoords.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<TexturePath> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		std::vector<TexturePath> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");

		//std::cout << "Diffuse maps length - " << diffuseMaps.size() << '\n';
		//std::cout << "Specular maps length - " << specularMaps.size() << '\n';
	}

	std::vector<float> verts = convertVertexesToFloatVector(vertices);
	return std::make_shared<mesh::ModelMesh>(verts, indices);
}

std::vector<float> ModelFactory::convertVertexesToFloatVector(const std::vector<mesh::Vertex>& vertexes) {
	size_t n = vertexes.size();
	std::vector<float> vertices(n * 8);

	for (size_t i = 0; i < n; i++) {
		vertices[i * 8 + 0] = vertexes[i].position.x;
		vertices[i * 8 + 1] = vertexes[i].position.y;
		vertices[i * 8 + 2] = vertexes[i].position.z;

		vertices[i * 8 + 3] = vertexes[i].normal.x;
		vertices[i * 8 + 4] = vertexes[i].normal.y;
		vertices[i * 8 + 5] = vertexes[i].normal.z;

		vertices[i * 8 + 6] = vertexes[i].textureCoords.x;
		vertices[i * 8 + 7] = vertexes[i].textureCoords.y;
	}
	return vertices;
}

std::vector<ModelFactory::TexturePath> ModelFactory::loadMaterialTexture(aiMaterial* material, aiTextureType type, const std::string& typeName) {
	std::vector<TexturePath> texturesList;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);
		std::string texturePath(str.C_Str());

		if (textures.find(texturePath) == textures.end()) {
			textures[texturePath] = TexturePath();
			textures[texturePath].path = texturePath;
			textures[texturePath].type = typeName;
		}

		texturesList.push_back(textures[texturePath]);
	}

	return texturesList;
}