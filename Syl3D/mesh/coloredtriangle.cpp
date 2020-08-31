#include "coloredtriangle.h"

using namespace mesh;

ColoredTriangle::ColoredTriangle() {
    _vertices = new float[] {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top 
    };

    _indices = new unsigned int[] {
        0, 1, 2
    };
}

ColoredTriangle::~ColoredTriangle() {
    delete[] _vertices;
    delete[] _indices;
}

float* ColoredTriangle::vertices() {
    return _vertices;
}

unsigned int* ColoredTriangle::indices() {
    return _indices;
}

size_t ColoredTriangle::numVertices() {
    return sizeof(float) * 18;
}

size_t ColoredTriangle::numIndices() {
    return sizeof(unsigned int) * 3;
}

std::vector<VertexAttributeData> ColoredTriangle::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 6 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(3, 6 * sizeof(float), 3 * sizeof(float)));
    return vertexAttribs;
}