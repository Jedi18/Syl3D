#include "triangle.h"

using namespace mesh;

Triangle::Triangle() {
    _vertices = new float[] {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    _indices = new unsigned int[] {
        0, 1, 2
    };
}

Triangle::~Triangle() {
    delete[] _vertices;
    delete[] _indices;
}

float* Triangle::vertices() {
    return _vertices;
}

unsigned int* Triangle::indices() {
    return _indices;
}

size_t Triangle::numVertices() {
    return sizeof(float) * 9;
}

size_t Triangle::numIndices() {
    return sizeof(unsigned int) * 3;
}

std::vector<VertexAttributeData> Triangle::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 3 * sizeof(float), 0));
    return vertexAttribs;
}