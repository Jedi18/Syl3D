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
		static void displayEntityEditor(std::shared_ptr<entity::Entity> selectedEntity);
	};
}

