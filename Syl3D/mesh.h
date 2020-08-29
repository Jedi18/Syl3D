#pragma once

#include <vector>

namespace mesh
{
	struct VertexAttributeData
	{
		VertexAttributeData(unsigned int size_in, size_t stride_in, size_t pointer_in) {
			size = size_in;
			stride = stride_in;
			pointer = pointer_in;
		}

		unsigned int size;
		size_t stride;
		size_t pointer;
	};

	class Mesh
	{
	public:
		virtual float* vertices() = 0;

		virtual unsigned int* indices() = 0;

		virtual size_t numVertices() = 0;

		virtual size_t numIndices() = 0;

		virtual std::vector<VertexAttributeData> vertexAttributes() = 0;
	};
}