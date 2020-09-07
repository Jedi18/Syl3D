#include "color.h"

using namespace shading;

Color::Color() 
	:
	r(255), g(255), b(255), a(1)
{}

Color::Color(float r, float g, float b) 
	:
	r(r), g(g), b(b), a(1)
{}

Color::Color(float r, float g, float b, float a)
	:
	r(r), g(g), b(b), a(a)
{}

Color::Color(int r, int g, int b) 
	:
	r((float)r/255.0f), g((float)g/255.0f), b((float)b/255.0f)
{}