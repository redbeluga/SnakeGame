#include "../include/SnakeObject.h"

SnakeObject::SnakeObject(){
  snakeHead = new GameObject(sf::Vector2f(150, 150), "Snake Head");
  circleShape = sf::CircleShape(20);
  circleShape.setFillColor(sf::Color::Blue);
  circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
  snakeHead->setCircleShape(circleShape, true, 0);

  snakeBodies.push_back(new GameObject(sf::Vector2f(0, circleShape.getRadius()*2), snakeHead, "Snake Body 1"));
  circleShape.setFillColor(sf::Color::Red);
  snakeBodies[0]->setCircleShape(circleShape, true, 1);
}

void SnakeObject::addBody(){
  snakeBodies.push_back(new GameObject(sf::Vector2f(circleShape.getRadius()*2*(-snakeBodies.back()->getCurDir().x), circleShape.getRadius()*2*(-snakeBodies.back()->getCurDir().y)), snakeBodies.back(), "Snake Body " + std::to_string(snakeBodies.size() + 1), snakeBodies.back()->getCurDir()));
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

void SnakeObject::newMove(sf::Vector2f move,sf::Vector2f location){
  sf::Vector2f queuedLoc(location.x, location.y);
  queuedLoc.x += (static_cast<int>(queuedLoc.x) % 40 == 0) ? 0 : 40 - static_cast<int>(queuedLoc.x) % 40;
  queuedLoc.y += (static_cast<int>(queuedLoc.y) % 40 == 0) ? 0 : 40 - static_cast<int>(queuedLoc.y) % 40;
  // std::cout << snakeHead->getAbsLoc().x << " : " << queuedLoc.x << std::endl;
  // std::cout << snakeHead->getAbsLoc().y << " : " << queuedLoc.y << std::endl << std::endl;

  // snakeHead->newMove(move, queuedLoc);
  snakeHead->setCurDir(move);
  snakeHead->getChildren()[0]->newMove(move, location);
}

void SnakeObject::updateMove(){
  snakeHead->updateMove();
}