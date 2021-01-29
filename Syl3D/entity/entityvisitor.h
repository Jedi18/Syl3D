#pragma once

#include <memory>

namespace entity
{
	class Cube;
	class Triangle;
	class Rectangle;
	class Circle;
	class UVSphere;
	class IcoSphere;
	class Terrain;
	class Model;

	class EntityVisitor
	{
	public:
		virtual void visit(entity::Cube* cube) = 0;

		virtual void visit(entity::Triangle* triangle) = 0;

		virtual void visit(entity::Rectangle* rectangle) = 0;

		virtual void visit(entity::Circle* circle) = 0;

		virtual void visit(entity::UVSphere* uvSphere) = 0;

		virtual void visit(entity::IcoSphere* icoSphere) = 0;

		virtual void visit(entity::Terrain* terrain) = 0;

		virtual void visit(entity::Model* model) = 0;
	};
}