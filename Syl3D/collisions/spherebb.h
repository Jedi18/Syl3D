#pragma once

#include "boundingbox.h"

namespace collisions
{
	class SphereBB : public BoundingBox
	{
	public:
		SphereBB(float r);

		bool intersects(const math::Vec3& boundingBoxCenter, const math::Ray& ray) const override;

		void setRadius(const float rad);

		void scaleRadius(const float factor);

	private:
		float radius;
	};
}
