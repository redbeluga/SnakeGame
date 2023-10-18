#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h" // Include the base class header
#include "GameObject.h"
#include "SnakeObject.h"
#include "SceneManager.h"

#include <unordered_map>
#include <vector>

class GameScene : public Scene {
  protected:
    SceneManager& sceneManager;
  private:
    //Time
    sf::Clock clock;
    float deltaTime;

    //Object Pools
    std::vector<GameObject*> allGameObjects;
    std::vector<GameObject*> renderedGameObjects;
    std::vector<sf::Shape*> backGroundSprites;

    //Input
    std::unordered_map<int, bool> keyMap;
    std::unordered_map<int, bool> tappedKeyMapping;

    //GameObjects
    bool moveInput = false;
    bool addBody = false;
    SnakeObject* snakeObject;
    sf::CircleShape* a;
    sf::CircleShape* b;

    // Event Poller
    sf::Event event;

    //Movement
    sf::Vector2f moveDir = sf::Vector2f(1, 0);

    //Board
    sf::RectangleShape* board;
    int startX;
    int startY;
    int columns = 17;
    int rows = 15;
    int cellSize = 40;


  public:
    GameScene(SceneManager& sceneManager); // Constructor
    virtual void start() override;
    virtual void inputHandler() override;
    virtual void update(sf::RenderWindow &window) override;
    virtual void render(sf::RenderWindow &window) override;
    virtual void eventPoller(sf::RenderWindow &window) override;
    void initializeGameObjects();
    void initializeBoard();
    void collisionCheck();
    void endGame();
    // void updateBoard(sf::RenderWindow &window);
};

#endif