#include "terrainmesh.h"

#include "../math/perlinnoise.h"

using namespace mesh;

TerrainMesh::TerrainMesh() {
    int rows = 10;
    int cols = 10;

    const double frequency = 0.5;
    const double fx = rows / frequency;
    const double fy = cols / frequency;

    std::vector<math::Vec3> vertices((rows+1) * (cols+1));

    int index = 0;
    for (int i = 0; i <= cols; i++) {
        for (int j = 0; j <= rows; j++) {
            float val = math::PerlinNoise::noise2D(i / fx, j / fy);
            vertices[index] = math::Vec3((((float)j / (float)rows) - 0.5f) * 2.0f, val, (((float)i/(float)cols) - 0.5f) * 2.0f);
            index++;
        }
    }

    indices_size = rows * cols * 6;
    _indices = new unsigned int[indices_size];
    index = 0;

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            _indices[index] = i * (rows + 1) + j;
            _indices[index + 1] = (i + 1) * (rows + 1) + j;
            _indices[index + 2] = (i + 1) * (rows + 1) + (j + 1);

            _indices[index + 3] = i * (rows + 1) + j;
            _indices[index + 4] = (i + 1) * (rows + 1) + (j + 1);
            _indices[index + 5] = i * (rows + 1) + (j + 1);

            index += 6;
        }
    }

    storeInVertices(vertices);
}

TerrainMesh::~TerrainMesh() {
    if (_vertices != nullptr) {
        delete[] _vertices;
    }

    if (_indices != nullptr) {
        delete[] _indices;
    }
}

float* TerrainMesh::vertices() {
    return _vertices;
}

unsigned int* TerrainMesh::indices() {
    return _indices;
}

size_t TerrainMesh::numVertices() {
    return vertices_size * sizeof(float);
}

size_t TerrainMesh::numIndices() {
    return indices_size * sizeof(unsigned int);
}

std::vector<VertexAttributeData> TerrainMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 3 * sizeof(float), 0));
    //vertexAttribs.push_back(VertexAttributeData(2, 5 * sizeof(float), 3 * sizeof(float)));
    return vertexAttribs;
}

void TerrainMesh::storeInVertices(std::vector<math::Vec3>& verts) {
    unsigned int n = verts.size();
    vertices_size = n * 3;
    _vertices = new float[vertices_size];

    unsigned int i = 0;
    for (math::Vec3& v : verts) {
        _vertices[i] = v.x;
        _vertices[i + 1] = v.y;
        _vertices[i + 2] = v.z;
        i += 3;
    }
}