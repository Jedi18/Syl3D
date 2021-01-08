#pragma once

#include "light.h"

namespace light
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(math::Vec3 direction, shading::Color diffuse);

		void setDirection(math::Vec3 dir);

		const math::Vec3 direction() const;

		void setShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, int index) override;

		LightType type() const override;

		void accept(LightVisitor& v) override;

	private:
		math::Vec3 _direction;
	};
}