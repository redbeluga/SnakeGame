#include "../../include/SceneManager.h"
#include "../../include/Scene.h"
#include <SFML/Graphics.hpp>

#include <iostream>

// Used to swap scenes

SceneManager::SceneManager(sf::RenderWindow &window) : currentScene(nullptr) {
  this->window = &window;
}

void SceneManager::changeScene(int index) {
  if(currentScene && currentScene->sceneIndex != index && index < scenes.size() || !currentScene){
    currentScene = scenes[index];
    currentScene->start();
  }
}

void SceneManager::update() {
  if (currentScene) {
    currentScene->update();
  }
}
void SceneManager::render() {
  if (currentScene) {
    currentScene->render();
  }
}
void SceneManager::eventPoller(){
  if(currentScene){
    currentScene->eventPoller();
  }
}

void SceneManager::inputHandler(){
  if(currentScene){
    currentScene->inputHandler();
  }
}

void SceneManager::addScene(Scene* scene){
  scene->setWindow(this->window);
  scenes.push_back(scene);
  scene->sceneIndex = scenes.size()-1;
}

int SceneManager::getCurrentIndex(){
  return currentScene->sceneIndex;
}

sf::RenderWindow* SceneManager::getRenderWindow(){
  return window;
}