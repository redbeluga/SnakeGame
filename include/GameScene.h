#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h" // Include the base class header
#include "GameObject.h"
#include "SnakeObject.h"
#include "SceneManager.h"
#include "SpriteManager.h"
#include "FontManager.h"

#include <unordered_map>
#include <vector>

class GameScene : public Scene {
  protected:
    SceneManager& sceneManager;
  private:
    //Time
    sf::Clock clock;
    float deltaTime;
    bool gameEnded = false;

    //Object Pools
    std::vector<GameObject*> allGameObjects;
    std::vector<GameObject*> renderedGameObjects;
    std::vector<sf::Shape*> backGroundSprites;
    sf::RectangleShape* filter;

    SnakeObject* snakeObject;
    SpriteManager spriteManager;
    std::vector<sf::Texture*> textures;
    std::vector<sf::Sprite> sprites;

    std::vector<sf::Text> text;
    FontManager& fontManager = FontManager::getInstance(); 
    std::map<std::string, sf::Font> fonts;


    //Input
    std::unordered_map<int, bool> keyMap;
    std::unordered_map<int, bool> tappedKeyMapping;

    //GameObjects
    bool moveInput = false;
    bool addBody = false;

    // Event Poller
    sf::Event event;

    //Movement
    sf::Vector2f moveDir;


  public:
    GameScene(SceneManager& sceneManager); // Constructor
    virtual void start() override;
    virtual void inputHandler() override;
    virtual void update() override;
    virtual void render() override;
    virtual void eventPoller() override;
    void initializeGameObjects();
    void initializeBoard();
    void initializeText();
    void collisionCheck();
    void endGame();
    void updateScore();
    // void updateBoard(sf::RenderWindow &window);

    //Board
    // sf::RectangleShape* board;
    std::vector<sf::Sprite> board;
    int startX = 40;
    int startY = 160;
    int endX;
    int endY;
    int columns = 17;
    int rows = 15;
    int cellSize = 40;
};

#endif