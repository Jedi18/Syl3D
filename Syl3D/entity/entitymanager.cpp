#include "entitymanager.h"

using namespace entity;

EntityManager* EntityManager::_instance = nullptr;

EntityManager::EntityManager() {

}

EntityManager* EntityManager::entityManager() {
	if (_instance == nullptr) {
		_instance = new EntityManager();
	}

	return _instance;
}

void EntityManager::releaseInstance() {
	if (_instance != nullptr) {
		delete _instance;
	}
}