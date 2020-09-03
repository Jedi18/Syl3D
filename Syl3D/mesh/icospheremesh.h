#pragma once

#include "mesh.h"
#include <vector>
#include <unordered_map>
#include "../math/vec3.h"

namespace mesh
{
	class IcoSphereMesh : public Mesh
	{
	public:
		struct TriangleIndices
		{
			TriangleIndices(unsigned int v1in, unsigned int v2in, unsigned int v3in) {
				v1 = v1in;
				v2 = v2in;
				v3 = v3in;
			}

			unsigned int v1;
			unsigned int v2;
			unsigned int v3;
		};
	public:
		IcoSphereMesh(int recursionLevel = 3);

		~IcoSphereMesh();

		float* vertices() override;

		unsigned int* indices() override;

		size_t numVertices() override;

		size_t numIndices() override;

		std::vector<VertexAttributeData> vertexAttributes() override;

	private:
		void addIndex(std::vector<unsigned int>& indices, unsigned int i, unsigned int j, unsigned int k);

		unsigned int getMiddlePoint(unsigned int v1, unsigned int v2, std::vector<math::Vec3>& vertices);

	private:
		float* _vertices;
		unsigned int* _indices;

		size_t vert_size;
		size_t indices_size;

		std::unordered_map<unsigned int, unsigned int> midPointCache;
	};
}