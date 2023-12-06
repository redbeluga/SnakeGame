#include "../../include/SceneManager.h"
#include "../../include/Scene.h"
#include <SFML/Graphics.hpp>

#include <iostream>

SceneManager::SceneManager() : currentScene(nullptr) {

}

void SceneManager::changeScene(int index) {
  if(currentScene && currentScene->sceneIndex != index && index < scenes.size() || !currentScene){
    currentScene = scenes[index];
    currentScene->start();
  }
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

void SceneManager::addScene(Scene* scene){
  scenes.push_back(scene);
  scene->sceneIndex = scenes.size()-1;
}

int SceneManager::getCurrentIndex(){
  return currentScene->sceneIndex;
}