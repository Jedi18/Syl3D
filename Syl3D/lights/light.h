#pragma once

#include "../shaderprogram.h"

#include <memory>

namespace light
{
	class Light
	{
	public:
		enum class LightType
		{
			Point,
			Directional,
			SpotLight
		};
	public:
		virtual void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) = 0;

		virtual LightType type() const = 0;
	};
}