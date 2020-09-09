#pragma once

#include "mesh.h"
#include <vector>
#include "../math/vec3.h"

#include "../utility/heightmapgenerator.h"

namespace mesh
{
	class TerrainMesh : public Mesh
	{
	public:
		TerrainMesh(utility::HeightmapData& heightmapData);

		~TerrainMesh();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

	private:
		void storeInVertices(std::vector<math::Vec3>& verts, std::vector<math::Vec3>& normals, int cols, float tilingX, float tilingY);

		math::Vec3 getTriangleNormal(math::Vec3 vert1, math::Vec3 vert2, math::Vec3 vert3);

	private:
		float* _vertices;
		unsigned int* _indices;

		unsigned int indices_size;
		unsigned int vertices_size;
	};
}