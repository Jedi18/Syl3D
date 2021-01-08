#pragma once

#include "light.h"

namespace light
{
	class PointLight : public Light
	{
	public:
		PointLight(math::Vec3 position, shading::Color diffuse);

		void setAmbientColor(shading::Color col);

		void setDiffuseColor(shading::Color col);

		void setSpecularColor(shading::Color col);

		void setConstant(float c);

		void setLinearConstant(float c);

		void setQuadraticConstant(float c);

		void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) override;

		LightType type() const override;

	private:
		shading::Color _ambient;
		shading::Color _diffuse;
		shading::Color _specular;

		float _constant;
		float _linearConstant;
		float _quadraticConstant;
	};
}