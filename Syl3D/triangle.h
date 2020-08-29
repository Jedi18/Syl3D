#pragma once

#include "mesh.h"

namespace mesh
{
	class Triangle : public Mesh
	{
	public:
		Triangle();

		~Triangle();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

	private:
		float* _vertices;
		unsigned int* _indices;
	};
}