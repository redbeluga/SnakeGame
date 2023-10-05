#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../include/Scene.h" // Include the base class header
#include "../../include/GameObject.h"

#include <unordered_map>
#include <vector>

class GameScene : public Scene {
  private:
    float deltaTime;
    std::vector<GameObject*> allGameObjects;
    std::vector<GameObject*> renderedGameObjects;

    std::unordered_map<int, bool> keyMap;
    std::unordered_map<int, bool> tappedKeyMapping;

    //GameObjects
    GameObject* snakeHead;
    GameObject* snakeBody;

    sf::Clock clock;
    sf::Event event;

    sf::Vector2f moveDir = sf::Vector2f(1, 0);

  public:
    GameScene(); // Constructor
    virtual void start() override;
    virtual void handleInput(sf::RenderWindow &window, sf::Event &event) override;
    virtual void update() override;
    virtual void render(sf::RenderWindow &window) override;
    virtual void eventPoller(sf::RenderWindow &window, sf::Event &event) override;
};

#endif