#include "objectguivisitor.h"

using namespace gui;

ImVec4 ObjectGUIVisitor::diffuse_color = ImVec4();
ImVec4 ObjectGUIVisitor::ambient_color = ImVec4();
ImVec4 ObjectGUIVisitor::specular_color = ImVec4();
float ObjectGUIVisitor::spot_cutoff = 12.5f;
float ObjectGUIVisitor::spot_outerCutoff = 17.5f;

void ObjectGUIVisitor::visit(entity::Cube* cube) {
	ImGui::Text("Cube");
}

void ObjectGUIVisitor::visit(entity::Triangle* triangle) {
	ImGui::Text("Triangle");
}

void ObjectGUIVisitor::visit(entity::Rectangle* rectangle) {
	ImGui::Text("Rectangle");
}

void ObjectGUIVisitor::visit(entity::UVSphere* uvSphere) {
	ImGui::Text("UVSphere");
}

void ObjectGUIVisitor::visit(entity::IcoSphere* icoSphere) {
	ImGui::Text("IcoSphere");
}

void ObjectGUIVisitor::visit(entity::Terrain* terrain) {
	ImGui::Text("Terrain");
}

void ObjectGUIVisitor::visit(entity::Model* model) {
	ImGui::Text("Model");
}

void ObjectGUIVisitor::visit(light::PointLight* point) {
	showDiffuseAmbientSpecular(point);
}

void ObjectGUIVisitor::visit(light::DirectionalLight* directional) {
	showDiffuseAmbientSpecular(directional);

	const math::Vec3 lightDir = directional->direction();
	float dirvec[4] = { lightDir.x, lightDir.y, lightDir.z };
	if (ImGui::SliderFloat3("Light Direction", dirvec, -3.14f, 3.14f)) {
		directional->setDirection(math::Vec3(dirvec[0], dirvec[1], dirvec[2]));
	}
}

void ObjectGUIVisitor::visit(light::SpotLight* spot) {
	showDiffuseAmbientSpecular(spot);

	const math::Vec3 lightDir = spot->direction();
	float dirvec[4] = { lightDir.x, lightDir.y, lightDir.z };
	if (ImGui::SliderFloat3("Light Direction", dirvec, -3.14f, 3.14f)) {
		spot->setDirection(math::Vec3(dirvec[0], dirvec[1], dirvec[2]));
	}

	spot_cutoff = spot->cutOff();
	if (ImGui::SliderFloat("Cutoff", &spot_cutoff, 0.0f, 1.0f, "%.3f")) {
		spot->setCutOff(spot_cutoff);
	}

	spot_outerCutoff = spot->outerCutOff();
	if (ImGui::SliderFloat("Outer Cutoff", &spot_outerCutoff, 0.0f, 1.0f, "%.3f")) {
		spot->setOuterCutOff(spot_outerCutoff);
	}
}

void ObjectGUIVisitor::showDiffuseAmbientSpecular(light::Light* light) {
	shading::Color current_diffuse = light->diffuseColor();
	diffuse_color = ImVec4(current_diffuse.r, current_diffuse.g, current_diffuse.b, current_diffuse.a);
	if (ImGui::ColorEdit3("Diffuse Color", (float*)&diffuse_color)) {
		light->setDiffuseColor(shading::Color(diffuse_color.x, diffuse_color.y, diffuse_color.z, diffuse_color.w));
	}

	shading::Color current_ambient = light->ambientColor();
	ambient_color = ImVec4(current_ambient.r, current_ambient.g, current_ambient.b, current_ambient.a);
	if (ImGui::ColorEdit3("Ambient Color", (float*)&ambient_color)) {
		light->setAmbientColor(shading::Color(ambient_color.x, ambient_color.y, ambient_color.z, ambient_color.w));
	}

	shading::Color current_specular = light->specularColor();
	specular_color = ImVec4(current_specular.r, current_specular.g, current_specular.b, current_specular.a);
	if (ImGui::ColorEdit3("Specular Color", (float*)&specular_color)) {
		light->setSpecularColor(shading::Color(specular_color.x, specular_color.y, specular_color.z, specular_color.w));
	}
}