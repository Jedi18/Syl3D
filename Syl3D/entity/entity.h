#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../base/object.h"
#include "../mesh/mesh.h"
#include "../math/vec3.h"
#include "../math/const.h"

#include "../texture/texturematerial.h"
#include "entityvisitor.h"

namespace entity
{
	class Entity : public Object
	{
	public:
		Entity();

		void initialize(const std::vector<std::shared_ptr<mesh::Mesh>>& mesh);

		virtual void draw() = 0;

		void setTexture(std::shared_ptr<TextureMaterial> texMaterial);

		std::shared_ptr<TextureMaterial> texture();

		void activateTexture();

	public:
		virtual void accept(EntityVisitor& v) = 0;

	protected:
		std::vector<unsigned int> _VAOs;
		bool _usesEBO;
		std::shared_ptr<TextureMaterial> _textureMaterial;
	};
}