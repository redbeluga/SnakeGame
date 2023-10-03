#include "GameObject.h"

std::pair<int, int> GameObject::getLoc(){
  return loc;
}
GameObject GameObject::getParent(){
  return *p;
}
GameObject::GameObject(std::pair<int, int> loc, GameObject* parent){
  this->loc = loc;
  p = parent;
}
GameObject::GameObject(std::pair<int, int> loc){
  this->loc = loc;
}