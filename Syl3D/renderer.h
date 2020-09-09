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

#include "lights/pointlight.h"
#include "lights/directionallight.h"
#include "lights/spotlight.h"

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
	EntityContainer _entityContainer;
	std::shared_ptr<light::SpotLight> _spotLight;
};