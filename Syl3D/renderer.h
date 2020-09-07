#pragma once

#include <vector>
#include <memory>

#include "shadermanager.h"
#include "texturematerial.h"
#include "entity/rectangle.h"
#include "entity/triangle.h"
#include "entity/cube.h"
#include "entity/uvsphere.h"
#include "entity/icosphere.h"
#include "entity/terrain.h"

#include "freecamera.h"
#include "mousepicker.h"
#include "entitycontainer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();

	void initialize(float window_width, float window_height);

	void render();

	void updateWindowDimensions(float window_width, float window_height);

	std::shared_ptr<FreeCamera> _freeCamera;
	MousePicker _mousePicker;

private:
	std::shared_ptr<ShaderManager> _shaderManager;
	std::shared_ptr<entity::UVSphere> lamp;
	EntityContainer _entityContainer;
};