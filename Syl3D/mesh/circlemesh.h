#pragma once

#include "mesh.h"

namespace mesh
{
	class CircleMesh : public Mesh
	{
	public:
		CircleMesh(int numPoints = 4);

		~CircleMesh();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

	private:
		float* _vertices;
		unsigned int* _indices;
		int numVerts;
		int numInds;
	};
}
