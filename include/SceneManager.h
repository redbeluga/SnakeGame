#ifndef SceneManager_H
#define SceneManager_H

#include <SFML/Graphics.hpp>
#include "Scene.h"

class SceneManager{
  public:
    SceneManager();
    void changeScene(Scene* scene);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
    void eventPoller(sf::RenderWindow &window);
    void inputHandler();
  private:
    Scene* currentScene;
};

#endif