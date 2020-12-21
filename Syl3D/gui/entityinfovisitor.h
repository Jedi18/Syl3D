#pragma once

#include "../entity/entityvisitor.h"

namespace gui
{
	class EntityInfoVisitor : public entity::EntityVisitor
	{
	public:
		void visit(entity::Cube* cube) override {
			data = "Cube";
		}

		void visit(entity::Triangle* triangle) override {
			data = "Triangle";
		}

		void visit(entity::Rectangle* rectangle) override {
			data = "Rectangle";
		}

		void visit(entity::UVSphere* uvSphere) override {
			data = "UVSphere";
		}

		void visit(entity::IcoSphere* icoSphere) override {
			data = "IcoSphere";
		}

		void visit(entity::Terrain* terrain) override {
			data = "Terrain";
		}

		void visit(entity::Model* model) override {
			data = "Model";
		}

		std::string getData() {
			return data;
		}

	private:
		std::string data;
	};
}

