#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../math/vec3.h"
#include "../math/const.h"

class Object
{
public:
	Object();

	Object(math::Vec3 position);

	virtual glm::mat4 modelMatrix();

	virtual void translate(math::Vec3 pos);

	virtual void translateTo(math::Vec3 pos);

	virtual void rotateX(float angleInRadians);

	virtual void rotateY(float angleInRadians);

	virtual void rotateZ(float angleInRadians);

	virtual void rotateAround(float angleInRadians, math::Vec3 axis);

	virtual void rotateTo(float angleInRadians, math::Vec3 axis);

	virtual glm::mat4 rotation() const;

	virtual void setRotation(glm::mat4 rot);

	virtual void scale(math::Vec3 scaleVec);

	virtual void scale(float factor);

	virtual void scaleX(float xfactor);

	virtual void scaleY(float yfactor);

	virtual void scaleZ(float zfactor);

	virtual void setScale(math::Vec3 scaleVec);

	virtual math::Vec3 position() const;

	virtual math::Vec3 getScale() const;

	unsigned int id() const;

protected:
	unsigned int _ID;
	math::Vec3 _pos;
	math::Vec3 _scale;
	glm::mat4 _rotation;
};

