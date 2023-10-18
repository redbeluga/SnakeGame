#include "../include/GameObject.h"
#include "../include/SceneManager.h"
#include "../include/GameObject.h"
#include "../include/GameScene.h"

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
  SceneManager sceneManager;
  GameScene gameScene(sceneManager);
  sceneManager.changeScene(&gameScene);
  

  while(renderWindow.isOpen()){
    sceneManager.eventPoller(renderWindow);
    sceneManager.inputHandler();
    sceneManager.update(renderWindow);
    sceneManager.render(renderWindow);
  }
  return 0;
}
