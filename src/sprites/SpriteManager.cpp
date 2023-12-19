#include "../../include/SpriteManager.h"

// The sprite manager spawns, despawns, and renders the apples on the ground for the snake to eat

SpriteManager::SpriteManager(){
  // Initializing the apples
  AppleObject* green = new AppleObject(0);
  green->createTexture();
  green->getTexture()->loadFromFile("../sprites/apple.png");
  green->getSprite()->setTexture(*(green->getTexture()));
  green->getSprite()->setOrigin(green->getSprite()->getLocalBounds().width / 2, green->getSprite()->getLocalBounds().height / 2);
  green->getSprite()->setScale(1.2f, 1.2f);
  green->getCircleShape()->setOrigin(green->getCircleShape()->getRadius(), green->getCircleShape()->getRadius());

  AppleObject* red = new AppleObject(1);
  red->createTexture();
  red->getTexture()->loadFromFile("../sprites/rat.png");
  red->getSprite()->setTexture(*(red->getTexture()));
  red->getSprite()->setOrigin(red->getSprite()->getLocalBounds().width / 2, red->getSprite()->getLocalBounds().height / 2);
  red->getSprite()->setScale(1.3f, 1.3f);
  red->getCircleShape()->setOrigin(red->getCircleShape()->getRadius(), red->getCircleShape()->getRadius());

  AppleObject* blue = new AppleObject(2);
  blue->createTexture();
  blue->getTexture()->loadFromFile("../sprites/pumpkin.png");
  blue->getSprite()->setTexture(*(blue->getTexture()));
  blue->getSprite()->setOrigin(blue->getSprite()->getLocalBounds().width / 2, blue->getSprite()->getLocalBounds().height / 2);
  blue->getSprite()->setScale(1.1f, 1.1f);
  blue->getCircleShape()->setOrigin(blue->getCircleShape()->getRadius(), blue->getCircleShape()->getRadius());


  applePool.push_back(green);
  applePool.push_back(red);
  applePool.push_back(blue);

  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void SpriteManager::spawnApple(){
  activeAppleIndex = std::rand() % 3;
  float spriteY, spriteX;
  
  // A check to make sure the apple is not spawning inside of the snake
  do{
    spriteY = startY + cellSize/2 + (std::rand() % rows) * cellSize;
    spriteX = startX + cellSize/2 + (std::rand() % columns) * cellSize;
    applePool[activeAppleIndex]->setAbsLoc(sf::Vector2f(spriteX, spriteY));
    applePool[activeAppleIndex]->setSpritePosition(sf::Vector2f(spriteX, spriteY));
    applePool[activeAppleIndex]->setCircleShapePosition(sf::Vector2f(spriteX, spriteY));
  }
  while(applePool[activeAppleIndex]->getCircleShape()->getGlobalBounds().intersects(snakeObject->snakeHead->getCircleShape()->getGlobalBounds()));
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
  window.draw(*(applePool[activeAppleIndex]->getSprite()));
}

void SpriteManager::setSnakeObject(SnakeObject* snakeObject){
  this->snakeObject = snakeObject;
}

AppleObject* SpriteManager::getCurrentApple(){
  if(activeAppleIndex == -1){
    return nullptr;
  }
  return applePool[activeAppleIndex];
}

void SpriteManager::eatApple(SnakeObject* snake){
  // increasing score after a snake eats an apple
  score++;
  spawnApple();
  snake->addBody();
}

void SpriteManager::reset(){
  score = 0;
}

int SpriteManager::getScore(){
  return score;
}