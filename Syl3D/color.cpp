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