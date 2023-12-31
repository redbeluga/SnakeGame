#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <iostream>
#include <vector>
#include <string>

class SnakeObject : public GameObject{
  public:
    GameObject* snakeHead;
    std::vector<GameObject*> snakeBodies;
    sf::CircleShape snakeHeadSprite;
    sf::CircleShape snakeBodySprite;
    sf::CircleShape circleShape;

    float startX, startY, cellSize;

    SnakeObject(float startX, float startY, float cellSize);
    
    void addBody();
    virtual void render(std::vector<GameObject*> &renderedGameObjects) override;
    // virtual void move(sf::Vector2f move);
    virtual void newMove(sf::Vector2f move, sf::Vector2f location);
    virtual void updateMove(float deltaTime) override;
};

#endif
