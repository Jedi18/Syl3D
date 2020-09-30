#include "ray.h"

using namespace math;

Ray::Ray() 
	:
	origin(0,0,0),
	direction(0,0,1)
{}

Ray::Ray(math::Vec3 o, math::Vec3 dir) 
	:
	origin(o),
	direction(dir)
{}