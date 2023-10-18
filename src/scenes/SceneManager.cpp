#include "../../include/SceneManager.h"
#include "../../include/Scene.h"
#include <SFML/Graphics.hpp>

SceneManager::SceneManager() : currentScene(nullptr) {

}

void SceneManager::changeScene(Scene* newScene) {
  currentScene = newScene;
}

void SceneManager::update(sf::RenderWindow &window) {
  if (currentScene) {
    currentScene->update(window);
  }
}
void SceneManager::render(sf::RenderWindow &window) {
  if (currentScene) {
    currentScene->render(window);
  }
}
void SceneManager::eventPoller(sf::RenderWindow &window){
  if(currentScene){
    currentScene->eventPoller(window);
  }
}
void SceneManager::inputHandler(){
  if(currentScene){
    currentScene->inputHandler();
  }
}