#pragma once

#include "../math/ray.h"

namespace collisions
{
	class BoundingBox
	{
	public:
		virtual bool intersects(const math::Vec3& boundingBoxCenter, const math::Ray& ray) const = 0;
	};
}
