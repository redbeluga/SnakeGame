#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
class SceneManager;

class Scene {
public:
  Scene(SceneManager& sceneManager);
  int sceneIndex;
  virtual void start() = 0;
  virtual void inputHandler() = 0;
  virtual void update(sf::RenderWindow &window) = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual void eventPoller(sf::RenderWindow &window) = 0;
protected:
  SceneManager& sceneManager;
};

#endif