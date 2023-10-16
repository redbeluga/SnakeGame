#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
public:
  virtual void start() = 0;
  virtual void handleInput() = 0;
  virtual void update(sf::RenderWindow &window) = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual void eventPoller(sf::RenderWindow &window) = 0;
};

#endif