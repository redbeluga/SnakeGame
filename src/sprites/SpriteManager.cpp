#include "../../include/SpriteManager.h"

SpriteManager::SpriteManager(){
  AppleObject* green = new AppleObject(0);
  green->getCircleShape()->setFillColor(sf::Color::Green);
  green->getCircleShape()->setOrigin(green->getCircleShape()->getRadius(), green->getCircleShape()->getRadius());
  AppleObject* red = new AppleObject(1);
  red->getCircleShape()->setFillColor(sf::Color::Red);
  red->getCircleShape()->setOrigin(red->getCircleShape()->getRadius(), red->getCircleShape()->getRadius());
  AppleObject* blue = new AppleObject(2);
  blue->getCircleShape()->setFillColor(sf::Color::Blue);
  blue->getCircleShape()->setOrigin(blue->getCircleShape()->getRadius(), blue->getCircleShape()->getRadius());

  applePool.push_back(green);
  applePool.push_back(red);
  applePool.push_back(blue);

  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void SpriteManager::spawnApple(){
  activeAppleIndex = std::rand() % 3;
  float spriteY = startY + cellSize + (std::rand() % rows) * cellSize;
  float spriteX = startX + cellSize + (std::rand() % columns) * cellSize;
  applePool[activeAppleIndex]->setAbsLoc(sf::Vector2f(spriteX, spriteY));
  applePool[activeAppleIndex]->setCircleShapePosition(sf::Vector2f(spriteX, spriteY));
}

void SpriteManager::setBoard(int startX, int startY, int columns, int rows, int cellSize){
  this->startX = startX;
  this->startY = startY;
  this->columns = columns;
  this->rows = rows;
  this->cellSize = cellSize;
}

void SpriteManager::renderCurrentApple(sf::RenderWindow &window){
  if(activeAppleIndex == -1) return;
  window.draw(*(applePool[activeAppleIndex]->getCircleShape()));
}

AppleObject* SpriteManager::getCurrentApple(){
  if(activeAppleIndex == -1){
    return nullptr;
  }
  return applePool[activeAppleIndex];
}

void SpriteManager::eatApple(SnakeObject* snake){
  score++;
  std::cout << score << std::endl;
  spawnApple();
  snake->addBody();
}

void SpriteManager::reset(){
  score = 0;
}