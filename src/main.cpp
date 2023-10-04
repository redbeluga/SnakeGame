#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <../include/GameObject.h>
// #include <src/Vector2.h>
#include <SFML/System/Vector2.hpp>


float deltaTime;

std::vector<GameObject> allGameObjects;
std::vector<GameObject*> renderedGameObjects;
std::unordered_map<int, bool> keys;
std::unordered_map<int, bool> tapKeys;
int temp = 0;

void inputHandler(sf::Keyboard::Key key, std::vector<int>& changedKeys);

void onUpdate(sf::RenderWindow& renderWindow);

void onStart();

void onAwake();

void onRender(sf::RenderWindow& renderWindow);

int main()
{
  sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");
  renderWindow.setKeyRepeatEnabled(false);

  sf::Event event;
  sf::Clock clock;

  onStart();

  while(renderWindow.isOpen()){
    tapKeys.clear();
    
    while (renderWindow.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        renderWindow.close();
      else if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased){
        if(event.type == sf::Event::EventType::KeyPressed){
          tapKeys[event.key.code] = true;
        }
          keys[event.key.code] = event.type == sf::Event::EventType::KeyPressed ? true : false;
      }
    }

    // std::cout << "Elapsed time since previous frame(microseconds): " << clock.getElapsedTime().asMicroseconds() << std::endl;
    deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    renderWindow.clear();
    onUpdate(renderWindow);
    onRender(renderWindow);
    renderWindow.display();
  }
  return 0;
}

void onStart(){
  // GameObject snakeObject;
  GameObject snakeObject = GameObject(sf::Vector2f(150, 150), "head");
  sf::CircleShape circleShape(10);
  circleShape.setFillColor(sf::Color::Blue);
  circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
  snakeObject.setCircleShape(circleShape);
  allGameObjects.push_back(snakeObject);

  GameObject bodyObject = GameObject(sf::Vector2f(0, circleShape.getRadius()), &allGameObjects[0], "body");
  circleShape.setFillColor(sf::Color::Red);
  bodyObject.setCircleShape(circleShape);

  allGameObjects.push_back(bodyObject);

  renderedGameObjects.push_back(&allGameObjects[0]);
  renderedGameObjects.push_back(&allGameObjects[1]);
}

void onUpdate(sf::RenderWindow& renderWindow){
  float vel = 5;
  sf::Vector2f moveVel = sf::Vector2f(0, 1);
  moveVel *= vel*deltaTime;
  if(tapKeys[sf::Keyboard::Key::F]){
    // renderedGameObjects[0]->moveCircleShape(moveVel);
  }
}

void move(GameObject g, sf::Vector2f move){

}

void onRender(sf::RenderWindow& renderWindow){
  for(GameObject* g : renderedGameObjects){
    // std::cout << g->getName() << ": " << g->getRelLoc().x << ", " << g->getRelLoc().y <<  std::endl;
    renderWindow.draw(g->getCircleShape());
  }
}