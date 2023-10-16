#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <queue>


class GameObject{
  private:
    sf::Vector2f absLoc;
    sf::Vector2f relLoc;
    sf::Clock clock;

    sf::CircleShape circleShape;

    float moveSpeed = 200;
    sf::Vector2f curDir = sf::Vector2f(0, -1);
    std::queue<sf::Vector2f> newDir;
    std::queue<sf::Vector2f> targetLocation;
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
    
    void setCurDir(sf::Vector2f dir);
    void setAbsLoc(sf::Vector2f absLoc);
    void setRelLoc(sf::Vector2f relLoc);
    void setParent(GameObject* p);
    void addChild(GameObject* c);
    void setCircleShape(sf::CircleShape CircleShape, bool shouldRender, int zIndex);
    void newMove(sf::Vector2f move, sf::Vector2f location);
    virtual void updateMove();
    void move();
    void setCircleShapePosition(sf::Vector2f newPos);
    void setShouldRender(bool render);
    virtual void render(std::vector<GameObject*> &renderedGameObjects);

    static bool compareByZIndex(const GameObject* a, const GameObject* b) {
        return a->zIndex > b->zIndex;
    }
    
    GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name, sf::Vector2f curDir);
    GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name);
    GameObject(sf::Vector2f absLoc, std::string name);
    GameObject(std::string name);
    GameObject();
};

#endif