#include "rectanglemesh.h"

using namespace mesh;

RectangleMesh::RectangleMesh() {
    _vertices = new float[20] {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
       -0.5f, 0.5f, 0.0f, 0.0f, 1.0f    // top left 
    };

    _indices = new unsigned int[6] {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
}

RectangleMesh::~RectangleMesh() {
    delete[] _vertices;
    delete[] _indices;
}

float* RectangleMesh::vertices() {
    return _vertices;
}

unsigned int* RectangleMesh::indices() {
    return _indices;
}

size_t RectangleMesh::numVertices() {
    return 20 * sizeof(float);
}

size_t RectangleMesh::numIndices() {
    return 6 * sizeof(unsigned int);
}

std::vector<VertexAttributeData> RectangleMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 5 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(2, 5 * sizeof(float), 3 * sizeof(float)));
    return vertexAttribs;
}