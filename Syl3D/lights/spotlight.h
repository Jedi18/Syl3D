#pragma once

#include "light.h"

namespace light
{
	class SpotLight : public Light
	{
	public:
		SpotLight(math::Vec3 position, math::Vec3 direction, shading::Color diffuse);

		void setDirection(math::Vec3 dir);

		const math::Vec3 direction() const;

		void setConstant(float c);

		void setLinearConstant(float c);

		void setQuadraticConstant(float c);

		void setCutOff(float c);

		float cutOff() const;

		void setOuterCutOff(float c);

		float outerCutOff() const;

		void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) override;

		LightType type() const override;

		void accept(LightVisitor& v) override;

	private:
		math::Vec3 _direction;

		float _constant;
		float _linearConstant;
		float _quadraticConstant;

		float _cutOff;
		float _outerCutOff;
	};
}
