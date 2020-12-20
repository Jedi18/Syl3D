#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../mesh/mesh.h"
#include "../math/vec3.h"
#include "../math/const.h"

#include "../texture/texturematerial.h"

namespace entity
{
	class Entity
	{
	public:
		Entity(std::string shaderName = "default");

		void initialize(const std::vector<std::shared_ptr<mesh::Mesh>>& mesh);

		virtual void draw() = 0;

		virtual glm::mat4 modelMatrix();

		virtual void translate(math::Vec3 pos);

		virtual void translateTo(math::Vec3 pos);

		virtual void rotateX(float angleInRadians);

		virtual void rotateY(float angleInRadians);

		virtual void rotateZ(float angleInRadians);

		virtual void rotateAround(float angleInRadians, math::Vec3 axis);

		virtual void rotateTo(float angleInRadians, math::Vec3 axis);

		virtual void scale(math::Vec3 scaleVec);

		virtual void scale(float factor);

		virtual void scaleX(float xfactor);

		virtual void scaleY(float yfactor);

		virtual void scaleZ(float zfactor);

		virtual math::Vec3 position() const;

		std::string shaderName() const;

		void setTexture(std::shared_ptr<TextureMaterial> texMaterial);

		void activateTexture();

	protected:
		std::vector<unsigned int> _VAOs;
		bool _usesEBO;
		math::Vec3 _pos;
		math::Vec3 _scale;
		glm::mat4 _rotation;
		std::string _shaderName;
		std::shared_ptr<TextureMaterial> _textureMaterial;
	};
}