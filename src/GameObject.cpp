#include "../include/GameObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>

GameObject* GameObject::getParent(){
  return p;
}
std::vector<GameObject*> GameObject::getChildren(){
  return c;
}
sf::CircleShape GameObject::getCircleShape(){
  return circleShape;
}
std::string GameObject::getName(){
  return name;
}
sf::Vector2f GameObject::getAbsLoc(){
  return absLoc;
}
sf::Vector2f GameObject::getRelLoc(){
  return relLoc;
}

void GameObject::setParent(GameObject* p){
  this->p = p;
}
void GameObject::addChild(GameObject* c){
  this->c.push_back(c);
}
void GameObject::setCircleShape(sf::CircleShape s){
  this->circleShape = s;
  setCircleShapePosition(absLoc);
}
void GameObject::moveCircleShape(sf::Vector2f moveDir){
  this->circleShape.move(moveDir);
  this->absLoc = circleShape.getPosition();
  for(GameObject* child : c){
    child->moveCircleShape(moveDir);
  }
}

void GameObject::setCircleShapePosition(sf::Vector2f newPos){
  this->circleShape.setPosition(newPos);
}

GameObject::GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name){
  this->relLoc = relLoc;
  this->absLoc = sf::Vector2f(parent->absLoc.x + relLoc.x, parent->absLoc.y + relLoc.y);
  p = parent;
  this->name = name;
  p->addChild(this);
}
GameObject::GameObject(sf::Vector2f absLoc, std::string name){
  this->absLoc = absLoc;
  this->relLoc = sf::Vector2f(0, 0);
  this->name = name;
}
GameObject::GameObject(std::string name){
  this->name = name;
}
GameObject::GameObject(){

}