// Include necessary headers
#include "../../include/Scene.h"

Scene::Scene(SceneManager& manager) : sceneManager(manager) {
}

void Scene::setWindow(sf::RenderWindow* window){
  this->window = window;
}
