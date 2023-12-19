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
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void eventPoller() = 0;
  void setWindow(sf::RenderWindow* window);
  

protected:
  SceneManager& sceneManager;
  sf::RenderWindow* window;
};

#endif