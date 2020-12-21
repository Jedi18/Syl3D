#include "guimanager.h"

#include <iostream>

#include "../entity/cube.h"
#include "../entity/entityfactory.h"
#include "../texture/texturefactory.h"

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
		EntityFactory* entityFactory = EntityFactory::entityFactory();
		TextureFactory* textureFactory = TextureFactory::textureFactory();
		std::shared_ptr<entity::Entity> cube = entityFactory->addEntity(EntityFactory::EntityType::Cube);
		cube->translateTo(math::Vec3(0.0f, 0.0f, 0.0f));
		cube->scale(5);
	}

	std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
	ImGui::Text("Current Selected Entity");
	std::string isselectedentity = (entityContainer->selectedEntity() == nullptr) ? "No entity selected" : "Entity selected!";
	ImGui::Text(isselectedentity.c_str());

	ImGui::End();
}