#include "circlemesh.h"
#include <cmath>
#include "../math/const.h"

using namespace mesh;

CircleMesh::CircleMesh(int numPoints) {
    numVerts = 3 * (numPoints + 1);
    _vertices = new float[numVerts];

    unsigned int index = 0;
    _vertices[index] = 0.0f;
    _vertices[index + 1] = 0.0f;
    _vertices[index + 2] = 0.0f;
    index++;

    const float increment = (2 * PI) / numPoints;
    float angle = 0.0f;

    for (int i = 0; i < numPoints; i++) {
        _vertices[3 * index] = 0.5f * std::cos(angle);
        _vertices[3 * index + 1] = 0.5f * std::sin(angle);
        _vertices[3 * index + 2] = 0.0f;

        angle += increment;
        index++;
    }

    numInds = 3 * (numPoints);
    _indices = new unsigned int[numInds];

    index = 0;
    for (unsigned int i = 0; i < numPoints; i++) {
        _indices[3 * index] = (i % numPoints) + 1;
        _indices[3 * index + 1] = 0;
        _indices[3 * index + 2] = (i + 1) % numPoints + 1;

        index++;
    }
}

CircleMesh::~CircleMesh() {
    delete[] _vertices;
    delete[] _indices;
}

float* CircleMesh::vertices() {
    return _vertices;
}

unsigned int* CircleMesh::indices() {
    return _indices;
}

size_t CircleMesh::numVertices() {
    return sizeof(float) * numVerts;
}

size_t CircleMesh::numIndices() {
    return sizeof(unsigned int) * numInds;
}

std::vector<VertexAttributeData> CircleMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 3 * sizeof(float), 0));
    return vertexAttribs;
}