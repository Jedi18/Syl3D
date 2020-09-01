#include "rectangle.h"

using namespace entity;

Rectangle::Rectangle() 
{
	this->initialize(&_rectangle);
}

void Rectangle::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}