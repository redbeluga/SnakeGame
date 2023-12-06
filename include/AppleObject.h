#ifndef APPLEOBJECT_H
#define APPLEOBJECT_H

#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <iostream>
#include <vector>
#include <string>

class AppleObject : public GameObject{
  public:
    bool isActive;
    int spriteIndex;
    AppleObject(int spriteIndex);
    void setActive(bool b);
};

#endif APPLEOBJECT_H