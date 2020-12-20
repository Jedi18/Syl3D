#include "guimanager.h"

#include <iostream>

GUIManager::GUIManager(EntityFactory& entityFactory)
	:
	entityFactory(entityFactory)
{}

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

void GUIManager::toolsMenu() {
	ImGui::Begin("Tools");
	ImGui::Text("Add Entity");

	if (ImGui::Button("Cube")) {
		std::cout << "Add a cube!!!!!!!!!" << std::endl;
	}

	ImGui::End();
}