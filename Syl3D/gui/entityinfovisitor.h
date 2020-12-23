#pragma once

#include "../entity/entityvisitor.h"

namespace gui
{
	class EntityInfoVisitor : public entity::EntityVisitor
	{
	public:
		struct EntityInfo
		{
			std::string entityTypeName;
		};

	public:
		void visit(entity::Cube* cube) override {
			data.entityTypeName = "Cube";
		}

		void visit(entity::Triangle* triangle) override {
			data.entityTypeName = "Triangle";
		}

		void visit(entity::Rectangle* rectangle) override {
			data.entityTypeName = "Rectangle";
		}

		void visit(entity::UVSphere* uvSphere) override {
			data.entityTypeName = "UVSphere";
		}

		void visit(entity::IcoSphere* icoSphere) override {
			data.entityTypeName = "IcoSphere";
		}

		void visit(entity::Terrain* terrain) override {
			data.entityTypeName = "Terrain";
		}

		void visit(entity::Model* model) override {
			data.entityTypeName = "Model";
		}

		EntityInfo getData() {
			return data;
		}

	private:
		EntityInfo data;
	};
}

