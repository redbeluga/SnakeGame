#ifndef SceneManager_H
#define SceneManager_H

#include <SFML/Graphics.hpp>
#include "Scene.h"

#include <vector>;

class SceneManager{
  public:
    SceneManager();
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
    void eventPoller(sf::RenderWindow &window);
    void inputHandler();
    void addScene(Scene* scene);
    void changeScene(int index);
    int getCurrentIndex();
  private:
    Scene* currentScene;
    std::vector<Scene*> scenes;
};

#endif