#pragma once

#include <vector>
#include <memory>

#include "shadermanager.h"
#include "texture/texturematerial.h"
#include "entity/rectangle.h"
#include "entity/triangle.h"
#include "entity/cube.h"
#include "entity/uvsphere.h"
#include "entity/icosphere.h"
#include "entity/terrain.h"
#include "entity/model.h"

#include "utility/modelfactory.h"

#include "lights/pointlight.h"
#include "lights/directionallight.h"
#include "lights/spotlight.h"

#include "freecamera.h"
#include "mousepicker.h"
#include "entity/entitycontainer.h"
#include "entity/entityfactory.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();

	/**
	 * Initialization
	 */
	void initialize(float window_width, float window_height);

	void render();

	void updateWindowDimensions(float window_width, float window_height);

	void mouseRayIntersections(math::Vec3 mouseRay);

	std::shared_ptr<FreeCamera> _freeCamera;
	MousePicker _mousePicker;

private:
	std::shared_ptr<ShaderManager> _shaderManager;
	std::shared_ptr<EntityContainer> _entityContainer;
	std::shared_ptr<light::SpotLight> _spotLight;

	std::vector<std::shared_ptr<entity::Cube>> _cubes;
	std::shared_ptr<TextureMaterial> _wallMaterial;
};