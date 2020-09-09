#include "icospheremesh.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "../math/vec3.h"

using namespace mesh;

IcoSphereMesh::IcoSphereMesh(int recursionLevel) {
	std::vector<math::Vec3> vertices;

	// http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html

	// create 12 vertices of a icosahedron
	double t = (1.0 + std::sqrt(5.0)) / 2.0;

	vertices.push_back(math::Vec3(-1, t, 0).normalized());
	vertices.push_back(math::Vec3(1, t, 0).normalized());
	vertices.push_back(math::Vec3(-1, -t, 0).normalized());
	vertices.push_back(math::Vec3(1, -t, 0).normalized());

	vertices.push_back(math::Vec3(0, -1, t).normalized());
	vertices.push_back(math::Vec3(0, 1, t).normalized());
	vertices.push_back(math::Vec3(0, -1, -t).normalized());
	vertices.push_back(math::Vec3(0, 1, -t).normalized());

	vertices.push_back(math::Vec3(t, 0, -1).normalized());
	vertices.push_back(math::Vec3(t, 0, 1).normalized());
	vertices.push_back(math::Vec3(-t, 0, -1).normalized());
	vertices.push_back(math::Vec3(-t, 0, 1).normalized());

	// create 20 triangles of the icosahedron
	// 5 faces around point 0
	// create 20 triangles of the icosahedron
	std::vector<TriangleIndices> faces;

	// 5 faces around point 0
	faces.push_back(TriangleIndices(0, 11, 5));
	faces.push_back(TriangleIndices(0, 5, 1));
	faces.push_back(TriangleIndices(0, 1, 7));
	faces.push_back(TriangleIndices(0, 7, 10));
	faces.push_back(TriangleIndices(0, 10, 11));

	faces.push_back(TriangleIndices(1, 5, 9));
	faces.push_back(TriangleIndices(5, 11, 4));
	faces.push_back(TriangleIndices(11, 10, 2));
	faces.push_back(TriangleIndices(10, 7, 6));
	faces.push_back(TriangleIndices(7, 1, 8));

	faces.push_back(TriangleIndices(3, 9, 4));
	faces.push_back(TriangleIndices(3, 4, 2));
	faces.push_back(TriangleIndices(3, 2, 6));
	faces.push_back(TriangleIndices(3, 6, 8));
	faces.push_back(TriangleIndices(3, 8, 9));

	faces.push_back(TriangleIndices(4, 9, 5));
	faces.push_back(TriangleIndices(2, 4, 11));
	faces.push_back(TriangleIndices(6, 2, 10));
	faces.push_back(TriangleIndices(8, 6, 7));
	faces.push_back(TriangleIndices(9, 8, 1));

	for (int i = 0; i < recursionLevel; i++) {
		std::vector<TriangleIndices> faces2;

		for (TriangleIndices tri : faces) {
			unsigned int a = getMiddlePoint(tri.v1, tri.v2, vertices);
			unsigned int b = getMiddlePoint(tri.v2, tri.v3, vertices);
			unsigned int c = getMiddlePoint(tri.v3, tri.v1, vertices);

			faces2.push_back(TriangleIndices(tri.v1, a, c));
			faces2.push_back(TriangleIndices(tri.v2, b, a));
			faces2.push_back(TriangleIndices(tri.v3, c, b));
			faces2.push_back(TriangleIndices(a, b, c));
		}

		faces = faces2;
	}

	vert_size = vertices.size() * 8;
	_vertices = new float[vert_size];

	int index = 0;
	for (int i = 0; i < vertices.size(); i++) {
		_vertices[index] = vertices[i].x;
		_vertices[index + 1] = vertices[i].y;
		_vertices[index + 2] = vertices[i].z;
		_vertices[index + 3] = vertices[i].x;
		_vertices[index + 4] = vertices[i].y;
		_vertices[index + 5] = vertices[i].z;

		// fix texture mapping
		_vertices[index + 6] = 1;
		_vertices[index + 7] = 1;

		index += 8;
	}

	indices_size = faces.size() * 3;
	_indices = new unsigned int[indices_size];
	index = 0;

	for (int j = 0; j < faces.size(); j++) {
		_indices[index] = faces[j].v1;
		_indices[index + 1] = faces[j].v2;
		_indices[index + 2] = faces[j].v3;
		index += 3;
	}
}

void IcoSphereMesh::addIndex(std::vector<unsigned int>& indices, unsigned int i, unsigned int j, unsigned int k) {
	indices.push_back(i);
	indices.push_back(j);
	indices.push_back(k);
}

unsigned int IcoSphereMesh::getMiddlePoint(unsigned int p1, unsigned int p2, std::vector<math::Vec3>& vertices) {
	// first check if we have it already
	bool firstIsSmaller = p1 < p2;
	unsigned int smallerIndex = firstIsSmaller ? p1 : p2;
	unsigned int greaterIndex = firstIsSmaller ? p2 : p1;
	unsigned int key = (smallerIndex << 32) + greaterIndex;

	if (midPointCache.find(key) != midPointCache.end()) {
		midPointCache[key];
	}

	// not in cache, calculate it
	math::Vec3 point1 = vertices[p1];
	math::Vec3 point2 = vertices[p2];
	math::Vec3 middle = math::Vec3(
		(point1.x + point2.x) / 2.0,
		(point1.y + point2.y) / 2.0,
		(point1.z + point2.z) / 2.0);

	// add vertex makes sure point is on unit sphere
	middle.normalize();
	int index = vertices.size();
	vertices.push_back(middle);

	// store it, return index
	midPointCache[key] = index;
	return index;
}

IcoSphereMesh::~IcoSphereMesh() {
	if (_vertices != nullptr) {
		delete[] _vertices;
	}

	if (_indices != nullptr) {
		delete[] _indices;
	}
}

float* IcoSphereMesh::vertices() {
	return _vertices;
}

unsigned int* IcoSphereMesh::indices() {
	return _indices;
}

size_t IcoSphereMesh::numVertices() {
	return vert_size * sizeof(float);
}

size_t IcoSphereMesh::numIndices() {
	return indices_size * sizeof(unsigned int);
}

std::vector<VertexAttributeData> IcoSphereMesh::vertexAttributes() {
	std::vector<VertexAttributeData> vertexAttribs;
	vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 0));
	vertexAttribs.push_back(VertexAttributeData(3, 8 * sizeof(float), 3 * sizeof(float)));
	vertexAttribs.push_back(VertexAttributeData(2, 8 * sizeof(float), 6 * sizeof(float)));
	return vertexAttribs;
}