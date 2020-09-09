#pragma once

#include "light.h"

namespace light
{
	class SpotLight : public Light
	{
	public:
		SpotLight(math::Vec3 position, math::Vec3 direction, shading::Color diffuse);

		void setPosition(math::Vec3 pos);

		void setDirection(math::Vec3 dir);

		void setAmbientColor(shading::Color col);

		void setDiffuseColor(shading::Color col);

		void setSpecularColor(shading::Color col);

		void setConstant(float c);

		void setLinearConstant(float c);

		void setQuadraticConstant(float c);

		void setCutOff(float c);

		void setOuterCutOff(float c);

		void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) override;

		LightType type() const override;

	private:
		math::Vec3 _position;
		math::Vec3 _direction;
		shading::Color _ambient;
		shading::Color _diffuse;
		shading::Color _specular;

		float _constant;
		float _linearConstant;
		float _quadraticConstant;

		float _cutOff;
		float _outerCutOff;
	};
}
