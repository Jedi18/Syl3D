#pragma once

#include "mesh.h"

namespace mesh
{
	class ModelMesh : public Mesh
	{
	public:
		ModelMesh();

		ModelMesh(const std::vector<float>& verts, const std::vector<unsigned int>& inds);

		~ModelMesh();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

		void setVertices(const std::vector<float>& verts);

		void setIndices(const std::vector<unsigned int>& inds);

	private:
		float* _vertices;
		unsigned int* _indices;
	};
}