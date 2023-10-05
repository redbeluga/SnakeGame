#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
public:
  virtual void start() = 0;
  virtual void handleInput(sf::RenderWindow &window, sf::Event &event) = 0;
  virtual void update() = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual void eventPoller(sf::RenderWindow &window, sf::Event &event) = 0;
};

#endif