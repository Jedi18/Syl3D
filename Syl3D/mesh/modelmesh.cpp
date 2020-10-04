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
    return _numVertices * sizeof(float);
}

size_t ModelMesh::numIndices() {
    return _numIndices * sizeof(unsigned int);
}

std::vector<VertexAttributeData> ModelMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 3 * sizeof(float)));
    vertexAttribs.push_back(VertexAttributeData(2, 8 * sizeof(float), 6 * sizeof(float)));
    return vertexAttribs;
}

void ModelMesh::setVertices(const std::vector<float>& verts) {
    _numVertices = verts.size();
    _vertices = new float[_numVertices];

    for (size_t i = 0; i < _numVertices; i++) {
        _vertices[i] = verts[i];
    }
}

void ModelMesh::setIndices(const std::vector<unsigned int>& inds) {
    _numIndices = inds.size();
    _indices = new unsigned int[_numIndices];

    for (size_t i = 0; i < _numIndices; i++) {
        _indices[i] = inds[i];
    }
}