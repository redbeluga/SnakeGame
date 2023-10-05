#include "../include/GameObject.h"
#include "scenes/GameScene.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>


float deltaTime;
// GameObject Pools
std::vector<GameObject*> allGameObjects;
std::vector<GameObject*> renderedGameObjects;

std::unordered_map<int, bool> keys;
std::unordered_map<int, bool> tapKeys;

//GameObjects
GameObject* snakeHead;
GameObject* snakeBody;

sf::Vector2f moveDir = sf::Vector2f(1, 0);

void inputHandler(sf::Keyboard::Key key, std::vector<int>& changedKeys);

void onUpdate(sf::RenderWindow& renderWindow);

void onStart();

void onAwake();

void onRender(sf::RenderWindow& renderWindow);

void gameObjectInitialize();

int main()
{
  sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");
  renderWindow.setKeyRepeatEnabled(false);

  GameScene gameScene;
  std::vector<Scene*> scenes;
  int activeSceneIndex = 0;

  scenes.push_back(&gameScene);

  sf::Event event;

  onStart();

  while(renderWindow.isOpen()){
    scenes[activeSceneIndex]->eventPoller(renderWindow, event);
    scenes[activeSceneIndex]->update();
    scenes[activeSceneIndex]->render(renderWindow);
  }
  return 0;
}

void onStart(){
  gameObjectInitialize();
}

void onUpdate(sf::RenderWindow& renderWindow){
  float vel = 40;
  if(tapKeys[sf::Keyboard::Key::W]){
    moveDir = sf::Vector2f(0, -1);
  }
  else if(tapKeys[sf::Keyboard::Key::S]){
    moveDir = sf::Vector2f(0, 1);
  }
  else if(tapKeys[sf::Keyboard::Key::A]){
    moveDir = sf::Vector2f(-1, 0);
  }
  else if(tapKeys[sf::Keyboard::Key::D]){
    moveDir = sf::Vector2f(1, 0);
  }
  sf::Vector2f moveVel = moveDir*vel*deltaTime;
  renderedGameObjects[0]->moveCircleShape(moveVel);
}

void onRender(sf::RenderWindow& renderWindow){
  for (std::vector<GameObject*>::reverse_iterator g = renderedGameObjects.rbegin(); g != renderedGameObjects.rend(); g++) { 
    renderWindow.draw((*g)->getCircleShape());
  }
}

void gameObjectInitialize(){
  snakeHead = new GameObject(sf::Vector2f(150, 150), "head");
  sf::CircleShape circleShape(10);
  circleShape.setFillColor(sf::Color::Blue);
  circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
  snakeHead->setCircleShape(circleShape);
  allGameObjects.push_back(snakeHead);

  snakeBody = new GameObject(sf::Vector2f(0, circleShape.getRadius()), snakeHead, "body");
  circleShape.setFillColor(sf::Color::Red);
  snakeBody->setCircleShape(circleShape);
  allGameObjects.push_back(snakeBody);
  std::cout << snakeBody << std::endl;

  renderedGameObjects.push_back(allGameObjects[0]);
  renderedGameObjects.push_back(allGameObjects[1]);
}