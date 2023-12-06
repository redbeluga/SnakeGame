#include "../../include/AppleObject.h"

AppleObject::AppleObject(int spriteIndex){
  setCircleShape(sf::CircleShape(20), false, 1);
  isActive = false;
  this->spriteIndex = spriteIndex;
}

void AppleObject::setActive(bool b){
  isActive = b;
}