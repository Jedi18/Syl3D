#pragma once

namespace light
{
	class PointLight;
	class DirectionalLight;
	class SpotLight;

	class LightVisitor
	{
	public:
		virtual void visit(light::PointLight* point) = 0;

		virtual void visit(light::DirectionalLight* directional) = 0;

		virtual void visit(light::SpotLight* spot) = 0;
	};
}
