#include "skyboxmanager.h"

#include "../entity/entityfactory.h"
#include "../utility/fileio.h"

SkyboxManager* SkyboxManager::_instance = nullptr;

SkyboxManager::SkyboxManager() {
	_skyboxNames = utility::FileIO::filesInPath("resources/skyboxes");
}

SkyboxManager* SkyboxManager::skyboxManager() {
	if (_instance == nullptr) {
		_instance = new SkyboxManager();
	}

	return _instance;
}

void SkyboxManager::releaseInstance() {
	if (_instance != nullptr) {
		delete _instance;
	}
}

void SkyboxManager::addSkybox(const std::string& skyboxName) {
	if (_skyboxes.find(skyboxName) != _skyboxes.end()) {
		setSkybox(skyboxName);
		return;
	}

	std::shared_ptr<CubeMap> skycubebox1 = std::make_shared<CubeMap>("resources/skyboxes/" + skyboxName);
	std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>();
	skybox->setCubemap(skycubebox1);
	_skyboxes[skyboxName] = skybox;
	setSkybox(skyboxName);
}

void SkyboxManager::setSkybox(const std::string& skyboxName) {
	if (_skyboxes.find(skyboxName) == _skyboxes.end()) {
		return;
	}

	EntityFactory::entityFactory()->entityContainer()->setSkybox(_skyboxes[skyboxName]);
}

const std::vector<std::string>& SkyboxManager::skyboxNames() const {
	return _skyboxNames;
}