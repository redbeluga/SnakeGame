#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "AppleObject.h"
#include "SnakeObject.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

class SpriteManager {
public:
  std::vector<AppleObject*> applePool;
  int activeAppleIndex = -1;
  AppleObject* getCurrentApple();
  void renderCurrentApple(sf::RenderWindow &window);  
  SpriteManager();
  void spawnApple();
  void setBoard(int startX, int startY, int columns, int rows, int cellSize);
  void eatApple(SnakeObject* snake);
  void reset();

private:
  int startX;
  int startY;
  int columns = 17;
  int rows = 15;
  int cellSize = 40;

  int score;
};
#endif
