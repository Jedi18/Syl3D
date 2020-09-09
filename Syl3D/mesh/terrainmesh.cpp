#include "terrainmesh.h"

using namespace mesh;

TerrainMesh::TerrainMesh(utility::HeightmapData& heightmapData) {
    int rows = heightmapData.rows;
    int cols = heightmapData.cols;

    std::vector<math::Vec3> vertices((rows + 1) * (cols + 1));
    std::vector<math::Vec3> normals((rows + 1) * (cols + 1));

    int index = 0;
    for (int i = 0; i <= cols; i++) {
        for (int j = 0; j <= rows; j++) {
            float val = heightmapData.heightmap[i + j * cols];
            vertices[index] = math::Vec3((((float)j / (float)rows) - 0.5f) * 2.0f, val, (((float)i/(float)cols) - 0.5f) * 2.0f);
            normals[index] = math::Vec3(0.0f, 0.0f, 0.0f);
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

            math::Vec3 norm1 = getTriangleNormal(vertices[_indices[index]], vertices[_indices[index + 1]], vertices[_indices[index + 2]]);
            norm1.normalize();
            normals[_indices[index]] += norm1;
            normals[_indices[index + 1]] += norm1;
            normals[_indices[index + 2]] += norm1;

            math::Vec3 norm2 = getTriangleNormal(vertices[_indices[index + 3]], vertices[_indices[index + 4]], vertices[_indices[index + 5]]);
            norm2.normalize();
            normals[_indices[index + 3]] += norm2;
            normals[_indices[index + 4]] += norm2;
            normals[_indices[index + 5]] += norm2;

            index += 6;
        }
    }

    storeInVertices(vertices, normals, cols, heightmapData.tilingX, heightmapData.tilingY);
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
    vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 3 * sizeof(float)));
    vertexAttribs.push_back(VertexAttributeData(2, 8 * sizeof(float), 6 * sizeof(float)));
    return vertexAttribs;
}

void TerrainMesh::storeInVertices(std::vector<math::Vec3>& verts, std::vector<math::Vec3>& normals, int cols, float tilingX, float tilingY) {
    unsigned int n = verts.size();
    vertices_size = n * 8;
    _vertices = new float[vertices_size];

    unsigned int i = 0;
    for (int j = 0; j < n; j++) {
        normals[j].normalize();

        _vertices[i] = verts[j].x;
        _vertices[i + 1] = verts[j].y;
        _vertices[i + 2] = verts[j].z;
        _vertices[i + 3] = normals[j].x;
        _vertices[i + 4] = normals[j].y;
        _vertices[i + 5] = normals[j].z;
        _vertices[i + 6] = (j / cols) / (float)cols  * tilingX;
        _vertices[i + 7] = (j % cols) / (float)cols * tilingY;
        i += 8;
    }
}

math::Vec3 TerrainMesh::getTriangleNormal(math::Vec3 vert1, math::Vec3 vert2, math::Vec3 vert3) {
    vert1 += math::Vec3(1.0f, 1.0f, 1.0f);
    vert2 += math::Vec3(1.0f, 1.0f, 1.0f);
    vert3 += math::Vec3(1.0f, 1.0f, 1.0f);
    math::Vec3 ab = vert2 - vert1;
    math::Vec3 ac = vert3 - vert1;
    return math::Vec3::cross(vert2, vert3);
}