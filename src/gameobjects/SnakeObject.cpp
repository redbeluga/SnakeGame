#include "../../include/SnakeObject.h"
#include "../../include/Tag.h"

// This class holds both the head of the snake as well as the body of the snake
// It helps keep track of the snack in one unifiied class

SnakeObject::SnakeObject(float startX, float startY, float cellSize){
  this->cellSize = cellSize;
  this->startX = startX;
  this->startY = startY;

  snakeHead = new GameObject(sf::Vector2f(startX + cellSize/2 + getCurDir().x*cellSize, startY + cellSize/2 + getCurDir().y*cellSize), "Snake Head", SNAKE);
  circleShape = sf::CircleShape(20);
  circleShape.setFillColor(sf::Color::Blue);
  circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
  snakeHead->setCircleShape(circleShape, true, 0);

  snakeBodies.push_back(new GameObject(sf::Vector2f(circleShape.getRadius()*2*getCurDir().x*-1, circleShape.getRadius()*2*getCurDir().y*-1), snakeHead, "Snake Body 1", SNAKE));
  circleShape.setFillColor(sf::Color::Red);
  snakeBodies[0]->setCircleShape(circleShape, true, 1);
}

void SnakeObject::addBody(){
  snakeBodies.push_back(new GameObject(sf::Vector2f(circleShape.getRadius()*2*(-snakeBodies.back()->getCurDir().x), circleShape.getRadius()*2*(-snakeBodies.back()->getCurDir().y)), snakeBodies.back(), "Snake Body " + std::to_string(snakeBodies.size() + 1), snakeBodies.back()->getCurDir(), SNAKE));
  snakeBodies.back()->setCircleShape(circleShape, true, snakeBodies.size()-1);
}

void SnakeObject::render(std::vector<GameObject*> &renderedGameObjects){
  if(getShouldRender()){
    renderedGameObjects.push_back(snakeHead);
    for(auto sB : snakeBodies){
      renderedGameObjects.push_back(sB);
    }
  }
}

void SnakeObject::newMove(sf::Vector2f move, sf::Vector2f location){
  sf::Vector2f curDir = snakeHead->getCurDir();
  if(move == curDir || curDir.x*move.x + curDir.y*move.y == -1) return;
  sf::Vector2f queuedLoc = GameObject::getNextLocation(location, curDir, startX, startY, snakeHead->getCircleShape()->getRadius()*2);
  snakeHead->newMove(move, queuedLoc);
}

void SnakeObject::updateMove(float deltaTime){
  snakeHead->updateMove(deltaTime);
}