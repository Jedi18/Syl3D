#pragma once

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace gui
{
	class ObjectList
	{
	public:
		static void ShowObjectList();

		static void setSelectedObject(int selectedObjectId);

	public:
		static bool open;
		static int selectedObject;
	};
}