#include <SFML/Graphics.hpp>
#include <list>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <src/GameObject.h>
using namespace std;


float deltaTime;
// GameObject snakeObject;

void inputHandler(sf::Keyboard::Key key, list<int>& changedKeys);

void onUpdate(sf::RenderWindow& renderWindow);

void onStart();

void onAwake();

int main()
{
  sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");
  renderWindow.setKeyRepeatEnabled(false);

  sf::Event event;
  sf::Clock clock;

  std::unordered_map<int, bool> keys;
  std::list<int> changedKeys;

  while(renderWindow.isOpen()){
    changedKeys.clear();
    while (renderWindow.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        renderWindow.close();
      else if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased){
        changedKeys.push_back(event.key.code);
        for(int cK : changedKeys){
          keys[cK] = event.type == sf::Event::EventType::KeyPressed ? true : false;
          cout << cK << ": " << keys[cK] << endl;
        }
      }
    }

    // std::cout << "Elapsed time since previous frame(microseconds): " << clock.getElapsedTime().asMicroseconds() << std::endl;
    deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    renderWindow.clear();
    onUpdate(renderWindow);
    renderWindow.display();
  }
    return 0;
}

void onStart(){
  // snakeObject.sayHi();
}

void onUpdate(sf::RenderWindow& renderWindow){
  
}