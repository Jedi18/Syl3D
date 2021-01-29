#pragma once

#include "../vendor/imgui/imgui.h"

#include "../lights/pointlight.h"
#include "../lights/directionallight.h"
#include "../lights/spotlight.h"

#include <string>
#include "../entity/entityvisitor.h"
#include "../lights/lightvisitor.h"

namespace gui
{
	class ObjectGUIVisitor : public entity::EntityVisitor, public light::LightVisitor
	{
	public:
		void visit(entity::Cube* cube) override;

		void visit(entity::Triangle* triangle) override;

		void visit(entity::Rectangle* rectangle) override;

		void visit(entity::Circle* circle) override;

		void visit(entity::UVSphere* uvSphere) override;

		void visit(entity::IcoSphere* icoSphere) override;

		void visit(entity::Terrain* terrain) override;

		void visit(entity::Model* model) override;

		void visit(light::PointLight* point) override;

		void visit(light::DirectionalLight* directional) override;

		void visit(light::SpotLight* spot) override;

	private:
		void showDiffuseAmbientSpecular(light::Light* light);

	private:
		static ImVec4 diffuse_color;
		static ImVec4 ambient_color;
		static ImVec4 specular_color;
		static float spot_cutoff;
		static float spot_outerCutoff;
	};
}

