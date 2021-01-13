#pragma once

#include "../base/object.h"
#include "../shaderprogram.h"

#include <memory>
#include "lightvisitor.h"

namespace light
{
	class Light : public Object
	{
	public:
		Light()
		{}

		Light(math::Vec3 position)
			:
			Object(position),
			_diffuse(1.0f, 1.0f, 1.0f),
			_ambient(0.05f, 0.05f, 0.05f),
			_specular(shading::Color(1.0f, 1.0f, 1.0f))
		{}

		Light(math::Vec3 position, shading::Color diffuse)
			:
			Object(position),
			_diffuse(diffuse),
			_ambient(0.05f, 0.05f, 0.05f),
			_specular(shading::Color(1.0f, 1.0f, 1.0f))
		{}

		enum class LightType
		{
			Point,
			Directional,
			SpotLight
		};

		void setAmbientColor(shading::Color col) {
			_ambient = col;
		}

		void setDiffuseColor(shading::Color col) {
			_diffuse = col;
		}

		void setSpecularColor(shading::Color col) {
			_specular = col;
		}

		shading::Color ambientColor() {
			return _ambient;
		}

		shading::Color diffuseColor() {
			return _diffuse;
		}

		shading::Color specularColor() {
			return _specular;
		}

	public:
		virtual void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) = 0;

		virtual LightType type() const = 0;

		virtual void accept(LightVisitor& v) = 0;

	protected:
		shading::Color _ambient;
		shading::Color _diffuse;
		shading::Color _specular;
	};
}