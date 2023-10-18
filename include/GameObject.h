#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Tag.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include <stack>


class GameObject{
  private:
    sf::Vector2f absLoc;
    sf::Vector2f relLoc;

    Tag tag;

    sf::CircleShape circleShape;

    float moveSpeed = 200;
    sf::Vector2f curDir = sf::Vector2f(0, -1);
    std::queue<sf::Vector2f> newDir;
    std::queue<sf::Vector2f> targetLocation;
    std::stack<sf::Vector2f> lastLocation;
    // bool newMoveQueued = false;
    float deltaTime;

    std::string name;
    GameObject* p;
    std::vector<GameObject*> c;
    bool shouldRender;
    int zIndex = 0;


  public:
    sf::Vector2f getCurDir();
    sf::Vector2f getAbsLoc();
    sf::Vector2f getRelLoc();
    int getZIndex();
    GameObject* getParent();
    std::vector<GameObject*> getChildren();
    sf::CircleShape getCircleShape();
    std::string getName();
    bool getShouldRender();
    static int isPassedLocationTarget(sf::Vector2f moveDirection, sf::Vector2f targetLocation, sf::Vector2f objectLocation);
    sf::Vector2f getLastLocation();
    static sf::Vector2f getNextLocation(sf::Vector2f curLoc, sf::Vector2f curDir);

    void setCurDir(sf::Vector2f dir);
    void setAbsLoc(sf::Vector2f absLoc);
    void setRelLoc(sf::Vector2f relLoc);
    void setParent(GameObject* p);
    void addChild(GameObject* c);
    void setCircleShape(sf::CircleShape CircleShape, bool shouldRender, int zIndex);
    void newMove(sf::Vector2f move, sf::Vector2f location);
    virtual void updateMove(float deltaTime);
    void move(float deltaTime);
    void setCircleShapePosition(sf::Vector2f newPos);
    void setShouldRender(bool render);
    virtual void render(std::vector<GameObject*> &renderedGameObjects);

    static bool compareByZIndex(const GameObject* a, const GameObject* b) {
        return a->zIndex > b->zIndex;
    }
    
    GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name, sf::Vector2f curDir, Tag tag);
    GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name, Tag tag);
    GameObject(sf::Vector2f absLoc, std::string name, Tag tag);
    GameObject(std::string name, Tag tag);
    GameObject();
};

#endif