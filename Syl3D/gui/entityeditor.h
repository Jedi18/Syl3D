#pragma once

#include "../entity/entity.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace gui
{
	class EntityEditor
	{
	public:
		static void displayEntityEditor(std::shared_ptr<Object> selectedObject);

	private:
		static void textureSelectedCallback(int selectedTexture);

	private:
		static int _selectedTexture;
		// to update entity texture when required instead of checking every frame
		static bool entityTextureUpdated;
		static std::shared_ptr<Object> currentObject;
		// is the current object an entity or light
		static bool isCurrentObjectAnEntity;
	};
}

