#include "../include/GameObject.h"
#include "scenes/GameScene.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

int main()
{
  sf::RenderWindow renderWindow(sf::VideoMode(1000, 1000), "SFML Demo");
  renderWindow.setKeyRepeatEnabled(false);

  GameScene gameScene;
  std::vector<Scene*> scenes;
  int activeSceneIndex = 0;

  scenes.push_back(&gameScene);

  while(renderWindow.isOpen()){
    scenes[activeSceneIndex]->eventPoller(renderWindow);
    scenes[activeSceneIndex]->handleInput();
    scenes[activeSceneIndex]->update(renderWindow);
    scenes[activeSceneIndex]->render(renderWindow);
  }
  return 0;
}
