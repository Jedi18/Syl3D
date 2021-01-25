#pragma once

#include <map>
#include <memory>
#include "../misc/skybox.h"

/**
* Skybox manager to manage loading of skyboxes
* Maintains list of available skyboes, loads on demand
* Checks if skybox is already loaded
*/
class SkyboxManager
{
public:
	static SkyboxManager* skyboxManager();

	static void releaseInstance();

	/**
	* Loads skybox if not already loaded and then sets it as the current skybox
	*/
	void addSkybox(const std::string& skyboxName);

	/**
	* Set the given skybox corresponding to the skybox name
	*/
	void setSkybox(const std::string& skyboxName);

	/**
	* Returns available skybox names
	*/
	const std::vector<std::string>& skyboxNames() const;

private:
	SkyboxManager();

private:
	static SkyboxManager* _instance;
	std::map<std::string, std::shared_ptr<Skybox>> _skyboxes;
	std::vector<std::string> _skyboxNames;
};

