#pragma once

#include "light.h"

namespace light
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(math::Vec3 direction, shading::Color diffuse);

		void setDirection(math::Vec3 dir);

		void setAmbientColor(shading::Color col);

		void setDiffuseColor(shading::Color col);

		void setSpecularColor(shading::Color col);

		void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) override;

		LightType type() const override;

		void accept(LightVisitor& v) override;

	private:
		math::Vec3 _direction;
		shading::Color _ambient;
		shading::Color _diffuse;
		shading::Color _specular;
	};
}