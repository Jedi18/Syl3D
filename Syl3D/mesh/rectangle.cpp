#include "rectangle.h"

using namespace mesh;

Rectangle::Rectangle() {
    _vertices = new float[] {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
       -0.5f, 0.5f, 0.0f, 0.0f, 1.0f    // top left 
    };

    _indices = new unsigned int[] {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
}

Rectangle::~Rectangle() {
    delete[] _vertices;
    delete[] _indices;
}

float* Rectangle::vertices() {
    return _vertices;
}

unsigned int* Rectangle::indices() {
    return _indices;
}

size_t Rectangle::numVertices() {
    return 20 * sizeof(float);
}

size_t Rectangle::numIndices() {
    return 6 * sizeof(unsigned int);
}

std::vector<VertexAttributeData> Rectangle::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 5 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(2, 5 * sizeof(float), 3 * sizeof(float)));
    return vertexAttribs;
}