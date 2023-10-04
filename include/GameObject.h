#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>


class GameObject{
  private:
    sf::Vector2f absLoc;
    sf::Vector2f relLoc;
    std::string name;
    GameObject* p;
    std::list<GameObject*> c;
    sf::CircleShape circleShape;

  public:
    sf::Vector2f getAbsLoc();
    sf::Vector2f getRelLoc();
    GameObject* getParent();
    std::list<GameObject*> getChildren();
    sf::CircleShape getCircleShape();
    std::string getName();
    
    // void setAbsLoc(sf::Vector2f absLoc);
    // void setRelLoc(sf::Vector2f relLoc);
    // void resetAbsLoc();
    void setParent(GameObject* p);
    void addChild(GameObject* c);
    void setCircleShape(sf::CircleShape CircleShape);
    void moveCircleShape(sf::Vector2f move);
    void setCircleShapePosition(sf::Vector2f newPos);

    void sayHi(){std::cout << "Locked and Loaded" << std::endl;}
    
    GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name);
    GameObject(sf::Vector2f absLoc, std::string name);
    GameObject(std::string name);
};

#endif