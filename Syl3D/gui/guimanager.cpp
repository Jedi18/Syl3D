#include "guimanager.h"

#include <iostream>

#include "../entity/entityfactory.h"

#include "entityeditor.h"
#include "entitycreator.h"
#include "terraingenerator.h"

using namespace gui;

void GUIManager::initialize(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	EntityCreator::Initialize();
	TerrainGenerator::Initialize();
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
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Tools");

	EntityCreator::displayEntityCreator();

	std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
	std::shared_ptr<Object> selectedObject = entityContainer->selectedObject();

	if (selectedObject == nullptr) {
		ImGui::End();
		return;
	}

	EntityEditor::displayEntityEditor(selectedObject);

	ImGui::End();
}