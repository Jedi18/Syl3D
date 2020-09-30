#include "modelmesh.h"

using namespace mesh;

ModelMesh::ModelMesh() {
    _vertices = nullptr;

    _indices = nullptr;
}

ModelMesh::~ModelMesh() {
    if (_vertices != nullptr) {
        delete[] _vertices;
    }

    if (_indices != nullptr) {
        delete[] _indices;
    }
}

float* ModelMesh::vertices() {
    return _vertices;
}

unsigned int* ModelMesh::indices() {
    return _indices;
}

size_t ModelMesh::numVertices() {
    return 0 * sizeof(float);
}

size_t ModelMesh::numIndices() {
    return 0;
}

std::vector<VertexAttributeData> ModelMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    return vertexAttribs;
}