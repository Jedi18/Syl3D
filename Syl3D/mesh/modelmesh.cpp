#include "modelmesh.h"

using namespace mesh;

ModelMesh::ModelMesh() 
    :
    _vertices(nullptr),
    _indices(nullptr)
{}

ModelMesh::ModelMesh(const std::vector<float>& verts, const std::vector<unsigned int>& inds)
    :
    ModelMesh()
{
    setVertices(verts);
    setIndices(inds);
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


void ModelMesh::setVertices(const std::vector<float>& verts) {
    size_t n = verts.size();
    _vertices = new float[n];

    for (size_t i = 0; i < n; i++) {
        _vertices[i] = verts[i];
    }
}

void ModelMesh::setIndices(const std::vector<unsigned int>& inds) {
    size_t n = inds.size();
    _indices = new unsigned int[n];

    for (size_t i = 0; i < n; i++) {
        _indices[i] = inds[i];
    }
}