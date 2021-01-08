#pragma once

#include <string>
#include "../entity/entityvisitor.h"
#include "../lights/lightvisitor.h"

namespace gui
{
	class ObjectInfoVisitor : public entity::EntityVisitor, public light::LightVisitor
	{
	public:
		struct ObjectInfo
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

		void visit(light::PointLight* point) override {
			data.entityTypeName = "Point Light";
		}

		void visit(light::DirectionalLight* directional) override {
			data.entityTypeName = "Directional Light";
		}

		void visit(light::SpotLight* spot) override {
			data.entityTypeName = "Spot Light";
		}

		ObjectInfo getData() {
			return data;
		}

	private:
		ObjectInfo data;
	};
}

