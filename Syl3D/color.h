#pragma once

namespace shading
{
	class Color
	{
	public:
		Color();

		Color(float r, float g, float b);

		Color(float r, float g, float b, float a);

	public:
		float r;
		float g;
		float b;
		float a;
	};
}