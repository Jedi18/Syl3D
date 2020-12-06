#pragma once

namespace shading
{
	class Color
	{
	public:
		Color();

		explicit Color(float r, float g, float b);

		explicit Color(float r, float g, float b, float a);

		explicit Color(int r, int g, int b);

		Color(const Color&);

		Color operator+ (const Color& A);

		Color operator- (const Color& A);

		void operator= (const Color& A);


	public:
		float r;
		float g;
		float b;
		float a;
	};
}