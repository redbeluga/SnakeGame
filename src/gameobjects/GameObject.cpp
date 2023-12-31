#include "../../include/GameObject.h"

#include "../../include/Tag.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// This was supposed to be for all game objects but it got a bit messy to implement
// now its only used for the snake circles


sf::Vector2f GameObject::getCurDir(){
  return curDir;
}
GameObject* GameObject::getParent(){
  return p;
}
std::vector<GameObject*> GameObject::getChildren(){
  return c;
}
sf::CircleShape* GameObject::getCircleShape(){
  return &circleShape;
}
sf::Texture* GameObject::getTexture(){
  return &texture;
}
sf::Sprite* GameObject::getSprite(){
  return &sprite;
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
sf::Vector2f GameObject::getLastLocation(){
  return lastLocation.top();
}


// This function calculates what its next location is in the board using a grid of cell size 40 by 40 pixels
sf::Vector2f GameObject::getNextLocation(sf::Vector2f curLoc, sf::Vector2f curDir, float startX, float startY, float cellSize){
  sf::Vector2f queuedLoc(curLoc.x - (startX + cellSize/2), curLoc.y - (startY + cellSize/2));
  int rX = static_cast<int>(queuedLoc.x) % 40;
  int rY = static_cast<int>(queuedLoc.y) % 40;
  queuedLoc.x = static_cast<int>(queuedLoc.x) + ((rX == 0 || curDir.x == 0) ? 0 : curDir.x > 0 ? (40 - rX) : -rX);
  queuedLoc.y = static_cast<int>(queuedLoc.y) + ((rY == 0 || curDir.y == 0) ? 0 : curDir.y > 0 ? (40 - rY) : -rY);

  return sf::Vector2f(queuedLoc.x + startX + cellSize/2, queuedLoc.y + startY + cellSize/2);
}
bool GameObject::getShouldRender(){
  return shouldRender;
}
int GameObject::getZIndex(){
  return zIndex;
}

// This checks if the a certain location is past another location depending on its direction of movement
int GameObject::isPassedLocationTarget(sf::Vector2f moveDirection, sf::Vector2f targetLocation, sf::Vector2f objectLocation){
  // Calculate the vector from object location to specified location
  if(moveDirection.x == 0){
    // std::cout << "UP DOWN" << std::endl;
    // std::cout << targetLocation.y <<  "; " << moveDirection.y << "; " << objectLocation.y << std::endl << std::endl;
    return targetLocation.y*moveDirection.y < objectLocation.y * moveDirection.y;
  }
  else{
    // std::cout << "LEFT RIGHT" << std::endl;
    // std::cout << targetLocation.x <<  "; " << moveDirection.x <<  "; " << objectLocation.x << std::endl << std::endl;
    return targetLocation.x*moveDirection.x < objectLocation.x * moveDirection.x;
  }
  // return true;
}

void GameObject::setCurDir(sf::Vector2f dir){
  curDir = dir;
}
void GameObject::setAbsLoc(sf::Vector2f absLoc){
  this->absLoc = absLoc;
}
void GameObject::setRelLoc(sf::Vector2f relLoc){
  this->relLoc = relLoc;
}
void GameObject::setParent(GameObject* p){
  this->p = p;
}
void GameObject::addChild(GameObject* c){
  this->c.push_back(c);
}
void GameObject::setCircleShape(sf::CircleShape s, bool shouldRender, int zIndex){
  this->circleShape = s;
  this->shouldRender = shouldRender;
  this->zIndex = zIndex;
  setCircleShapePosition(absLoc);
}
void GameObject::setSprite(sf::Sprite s, bool shouldRender, int zIndex){
  this->sprite = s;
  this->shouldRender = shouldRender;
  this->zIndex = zIndex;
  setSpritePosition(absLoc);
}
void GameObject::createTexture(){
  texture = sf::Texture();
}

// The next three functions are used to move the snake in an orerly function
// It logs the location of where the snake should make a turn in a queue 
// When it reaches the location, it makes its turn
// After it makes the turn, it sends that location to the queue of its child
// so that its child knows to make the turn when it reaches that location
void GameObject::newMove(sf::Vector2f moveDir, sf::Vector2f location){
  newDir.push(moveDir);
  targetLocation.push(location);
  // std::cout << getName() << " queued loc: " << targetLocation.front().x << ", " << targetLocation.front().y << std::endl; 
}

void GameObject::updateMove(float deltaTime){
  move(deltaTime);
  if(targetLocation.size() > 0 && isPassedLocationTarget(curDir, targetLocation.front(), circleShape.getPosition())){
    curDir = newDir.front();
    float dx = abs(absLoc.x - targetLocation.front().x);
    float dy = abs(absLoc.y - targetLocation.front().y);
    sf::Vector2f newLoc;
    if(dx != 0){
      newLoc = sf::Vector2f(targetLocation.front().x, targetLocation.front().y + dx*newDir.front().y);
    }
    else{
      newLoc = sf::Vector2f(targetLocation.front().x + dy*newDir.front().x, targetLocation.front().y);
    }
    circleShape.setPosition(newLoc);
    setAbsLoc(circleShape.getPosition());
    for(auto c : this->getChildren()){
      c->newMove(curDir, targetLocation.front());
    }
    newDir.pop();
    lastLocation.push(targetLocation.front());
    targetLocation.pop();
  }
  for(auto c : getChildren()){
    c->updateMove(deltaTime);
  }
}

void GameObject::move(float deltaTime){
  sf::Vector2f moveDir = moveSpeed * deltaTime * curDir;
  this->circleShape.move(moveDir);
  absLoc = circleShape.getPosition();
}

void GameObject::setCircleShapePosition(sf::Vector2f newPos){
  this->circleShape.setPosition(newPos);
}
void GameObject::setSpritePosition(sf::Vector2f newPos){
  this->sprite.setPosition(newPos);
} 
void GameObject::setShouldRender(bool render){
  this->shouldRender = render;
}
void GameObject::render(std::vector<GameObject*> &renderedGameObjects){
  if(shouldRender){
    renderedGameObjects.push_back(this);
    for(auto child : c){
      if(child->getShouldRender()){
        child->render(renderedGameObjects);
      }
    }
  }
}

GameObject::GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name, sf::Vector2f curDir, Tag tag){
  this->tag = tag;
  this->curDir = curDir;
  this->relLoc = relLoc;
  // std::cout << relLoc.x << ", " << relLoc.y << std::endl;
  this->absLoc = sf::Vector2f(parent->absLoc.x + relLoc.x, parent->absLoc.y + relLoc.y);
  this->lastLocation.push(absLoc);
  p = parent;
  this->name = name;
  p->addChild(this);
}
GameObject::GameObject(sf::Vector2f relLoc, GameObject* parent, std::string name, Tag tag){
  this->tag = tag;
  this->relLoc = relLoc;
  // std::cout << relLoc.x << ", " << relLoc.y << std::endl;
  this->absLoc = sf::Vector2f(parent->absLoc.x + relLoc.x, parent->absLoc.y + relLoc.y);
  this->lastLocation.push(absLoc);
  p = parent;
  this->name = name;
  p->addChild(this);
}
GameObject::GameObject(sf::Vector2f absLoc, std::string name, Tag tag){
  this->tag = tag;
  this->absLoc = absLoc;
  this->lastLocation.push(absLoc);
  this->relLoc = sf::Vector2f(0, 0);
  this->name = name;
}
GameObject::GameObject(std::string name, Tag tag){
  this->tag = tag;
  this->name = name;
}
GameObject::GameObject(){

}