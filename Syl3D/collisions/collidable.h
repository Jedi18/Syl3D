#pragma once

#include "../math/ray.h"
#include "boundingbox.h"

namespace collisions
{
	class Collidable
	{
	public:
		Collidable(BoundingBox* boundingBox)
			:
			_boundingBox(boundingBox)
		{}

		virtual bool intersects(const math::Ray& ray) const = 0;

		~Collidable() {
			delete _boundingBox;
		}

	protected:
		BoundingBox* _boundingBox;
	};
}