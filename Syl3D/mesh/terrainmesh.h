#pragma once

#include "mesh.h"
#include <vector>
#include "../math/vec3.h"

namespace mesh
{
	class TerrainMesh : public Mesh
	{
	public:
		TerrainMesh();

		~TerrainMesh();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

	private:
		void storeInVertices(std::vector<math::Vec3>& verts);

	private:
		float* _vertices;
		unsigned int* _indices;

		unsigned int indices_size;
		unsigned int vertices_size;
	};
}