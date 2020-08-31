#include "trianglemesh.h"

using namespace mesh;

TriangleMesh::TriangleMesh() {
    _vertices = new float[] {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.5f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f
    };

    _indices = new unsigned int[] {
        0, 1, 2
    };
}

TriangleMesh::~TriangleMesh() {
    delete[] _vertices;
    delete[] _indices;
}

float* TriangleMesh::vertices() {
    return _vertices;
}

unsigned int* TriangleMesh::indices() {
    return _indices;
}

size_t TriangleMesh::numVertices() {
    return sizeof(float) * 15;
}

size_t TriangleMesh::numIndices() {
    return sizeof(unsigned int) * 3;
}

std::vector<VertexAttributeData> TriangleMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 5 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(2, 5 * sizeof(float), 3 * sizeof(float)));
    return vertexAttribs;
}