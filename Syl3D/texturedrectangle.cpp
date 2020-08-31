#include "texturedrectangle.h"

using namespace mesh;

TexturedRectangle::TexturedRectangle() {
    _vertices = new float[] {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
       -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left 
    };

    _indices = new unsigned int[] {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
}

TexturedRectangle::~TexturedRectangle() {
    delete[] _vertices;
    delete[] _indices;
}

float* TexturedRectangle::vertices() {
    return _vertices;
}

unsigned int* TexturedRectangle::indices() {
    return _indices;
}

size_t TexturedRectangle::numVertices() {
    return 32 * sizeof(float);
}

size_t TexturedRectangle::numIndices() {
    return 6 * sizeof(unsigned int);
}

std::vector<VertexAttributeData> TexturedRectangle::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 0));
    vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 3 * sizeof(float)));
    vertexAttribs.push_back(VertexAttributeData(2, 8 * sizeof(float), 6 * sizeof(float)));
    return vertexAttribs;
}