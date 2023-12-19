#include "../include/GameObject.h"
#include "../include/SceneManager.h"
#include "../include/GameObject.h"
#include "../include/GameScene.h"
#include "../include/MainMenuScene.h"
#include "../include/EndScene.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

int main()
{
  // Creating new window for SFML
  int width = sf::VideoMode::getDesktopMode().width;
  int height = sf::VideoMode::getDesktopMode().height;
  // std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height;
  sf::RenderWindow renderWindow(sf::VideoMode(width, height), "Snake In Your Garden", sf::Style::Resize);
  renderWindow.setKeyRepeatEnabled(false);

  // Adding scenes to the Scene Manager
  SceneManager sceneManager(renderWindow);
  sceneManager.addScene(new GameScene(sceneManager));
  sceneManager.addScene(new MainMenuScene(sceneManager));
  sceneManager.addScene(new EndScene(sceneManager));
  sceneManager.changeScene(1);

  // Update cycle 

  while(renderWindow.isOpen()){
    sceneManager.eventPoller();
    sceneManager.inputHandler();
    sceneManager.update();
    sceneManager.render();
  }
  return 0;
}
