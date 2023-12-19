#include "../../include/AppleObject.h"

// Used for the apples on the ground
// The circle shape is used as a circle collider for the collision detections
AppleObject::AppleObject(int spriteIndex){
  setSprite(sf::Sprite(), false, 1);
  setCircleShape(sf::CircleShape(20), false, 1);
  getCircleShape()->setFillColor(sf::Color::Green);
  isActive = false;
  this->spriteIndex = spriteIndex;
}

void AppleObject::setActive(bool b){
  isActive = b;
}