#pragma once

#include "light.h"

namespace light
{
	class PointLight : public Light
	{
	public:
		PointLight(math::Vec3 position, shading::Color diffuse);

		void setConstant(float c);

		void setLinearConstant(float c);

		void setQuadraticConstant(float c);

		void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) override;

		LightType type() const override;

		void accept(LightVisitor& v) override;

	private:
		float _constant;
		float _linearConstant;
		float _quadraticConstant;
	};
}