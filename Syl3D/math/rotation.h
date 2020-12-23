#pragma once

#include "vec3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

namespace math
{
	class Rotation
	{
	public:
		static Vec3 MatToEulerAngles(glm::mat4 rot) {
			Vec3 result;
			result.x = std::atan2f(rot[2][1], rot[2][2]);
			result.y = std::atan2f(-rot[2][0], std::sqrtf((rot[2][1] * rot[2][1]) + (rot[2][2] * rot[2][2])));
			result.z = std::atan2f(rot[1][0], rot[0][0]);
			return result;
		}
	};
}