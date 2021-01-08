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
			Object(position)
		{}

		enum class LightType
		{
			Point,
			Directional,
			SpotLight
		};
	public:
		virtual void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) = 0;

		virtual LightType type() const = 0;

		virtual void accept(LightVisitor& v) = 0;
	};
}