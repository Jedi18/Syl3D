#include "guimanager.h"

#include <iostream>

#include "../entity/entityfactory.h"

#include "entityeditor.h"
#include "entitycreator.h"

using namespace gui;

void GUIManager::initialize(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void GUIManager::render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow(&show_demo_window);
	toolsMenu();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::cleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool GUIManager::mouseOnGUI() const {
	return ImGui::IsAnyWindowHovered();
}

void GUIManager::toolsMenu() {
	ImGui::Begin("Tools");

	EntityCreator::displayEntityCreator();

	std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
	std::shared_ptr<entity::Entity> selectedEntity = entityContainer->selectedEntity();

	EntityEditor::displayEntityEditor(selectedEntity);

	ImGui::End();
	//ImGui::ShowDemoWindow();
}