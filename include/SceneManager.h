#ifndef SceneManager_H
#define SceneManager_H

#include <SFML/Graphics.hpp>
#include "Scene.h"

#include <vector>;

class SceneManager{
  public:
    SceneManager(sf::RenderWindow &window);
    void update();
    void render();
    void eventPoller();
    void inputHandler();
    void addScene(Scene* scene);
    void changeScene(int index);
    int getCurrentIndex();
    sf::RenderWindow* getRenderWindow();
  private:
    Scene* currentScene;
    std::vector<Scene*> scenes;
    sf::RenderWindow* window;
};

#endif