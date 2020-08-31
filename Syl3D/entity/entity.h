#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../mesh/mesh.h"

namespace entity
{
	class Entity
	{
	public:
		void initialize(mesh::Mesh* mesh);

		virtual void draw() = 0;

	protected:
		unsigned int _VAO;
	};
}