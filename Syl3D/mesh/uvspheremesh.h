#pragma once

#include "mesh.h"
#include <vector>
#include "../math/vec3.h"

namespace mesh
{
	class UVSphereMesh : public Mesh
	{
	public:
		UVSphereMesh(int parallels = 10, int meridians = 10);

		~UVSphereMesh();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

	private:
		float* _vertices;
		unsigned int* _indices;

		size_t vert_size;
		size_t indices_size;
	};
}