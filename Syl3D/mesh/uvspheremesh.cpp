#include "uvspheremesh.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "../math/vec3.h"

using namespace mesh;

UVSphereMesh::UVSphereMesh(int parallels, int meridians) {
	std::vector<math::Vec3> vertices;
	std::vector<int> indices;

	// Some code borrowed from Oscar Sebio Cajaraville's Sphere's github repo

	const double M_PI = 3.14159265;

	vertices.emplace_back(0.0f, 1.0f, 0.0f);
	for (uint32_t j = 0; j < parallels - 1; ++j)
	{
		double const polar = M_PI * double(j + 1) / double(parallels);
		double const sp = std::sin(polar);
		double const cp = std::cos(polar);
		for (uint32_t i = 0; i < meridians; ++i)
		{
			double const azimuth = 2.0 * M_PI * double(i) / double(meridians);
			double const sa = std::sin(azimuth);
			double const ca = std::cos(azimuth);
			double const x = sp * ca;
			double const y = cp;
			double const z = sp * sa;
			vertices.emplace_back(x, y, z);
		}
	}
	vertices.emplace_back(0.0f, -1.0f, 0.0f);

	for (uint32_t i = 0; i < meridians; ++i)
	{
		uint32_t const a = i + 1;
		uint32_t const b = (i + 1) % meridians + 1;
		indices.emplace_back(0);
		indices.emplace_back(b);
		indices.emplace_back(a);
	}

	for (uint32_t j = 0; j < parallels - 2; ++j)
	{
		uint32_t aStart = j * meridians + 1;
		uint32_t bStart = (j + 1) * meridians + 1;
		for (uint32_t i = 0; i < meridians; ++i)
		{
			const uint32_t a = aStart + i;
			const uint32_t a1 = aStart + (i + 1) % meridians;
			const uint32_t b = bStart + i;
			const uint32_t b1 = bStart + (i + 1) % meridians;

			indices.emplace_back(a);
			indices.emplace_back(a1);
			indices.emplace_back(b1);
			indices.emplace_back(a);
			indices.emplace_back(b1);
			indices.emplace_back(b);
		}
	}

	for (uint32_t i = 0; i < meridians; ++i)
	{
		uint32_t const a = i + meridians * (parallels - 2) + 1;
		uint32_t const b = (i + 1) % meridians + meridians * (parallels - 2) + 1;
		indices.emplace_back(vertices.size() - 1);
		indices.emplace_back(a);
		indices.emplace_back(b);
	}

	vert_size = vertices.size() * 3;
	indices_size = indices.size();

	_vertices = new float[vert_size];

	int index = 0;
	for (int i = 0; i < vertices.size(); i++) {
		_vertices[index] = vertices[i].x;
		_vertices[index + 1] = vertices[i].y;
		_vertices[index + 2] = vertices[i].z;
		index += 3;
	}

	_indices = new unsigned int[indices_size];
	for (int j = 0; j < indices_size; j++) {
		_indices[j] = indices[j];
	}
}

UVSphereMesh::~UVSphereMesh() {
    if (_vertices != nullptr) {
        delete[] _vertices;
    }

    if (_indices != nullptr) {
        delete[] _indices;
    }
}

float* UVSphereMesh::vertices() {
    return _vertices;
}

unsigned int* UVSphereMesh::indices() {
    return _indices;
}

size_t UVSphereMesh::numVertices() {
    return vert_size * sizeof(float);
}

size_t UVSphereMesh::numIndices() {
    return indices_size * sizeof(unsigned int);
}

std::vector<VertexAttributeData> UVSphereMesh::vertexAttributes() {
    std::vector<VertexAttributeData> vertexAttribs;
    vertexAttribs.push_back(VertexAttributeData(3, 3 * sizeof(float), 0));
    return vertexAttribs;
}