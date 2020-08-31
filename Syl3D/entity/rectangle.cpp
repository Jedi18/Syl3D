#include "rectangle.h"

using namespace entity;

Rectangle::Rectangle() 
{
	this->initialize(&_rectangle);
}

void Rectangle::draw() {
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}