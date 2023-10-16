#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <../include/GameObject.h>
#include <string>

class SnakeObject : public GameObject{
  public:
    GameObject* snakeHead;
    std::vector<GameObject*> snakeBodies;
    sf::CircleShape snakeHeadSprite;
    sf::CircleShape snakeBodySprite;
    sf::CircleShape circleShape;

    SnakeObject();
    
    void addBody();
    virtual void render(std::vector<GameObject*> &renderedGameObjects) override;
    // virtual void move(sf::Vector2f move);
    virtual void newMove(sf::Vector2f move, sf::Vector2f location);
    virtual void updateMove() override;
};

#endif
