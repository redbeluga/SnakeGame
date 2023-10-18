// Include necessary headers
#include "../../include/GameScene.h"

#include "../../include/EndScene.h"
#include "../../include/Scene.h" // Include the base class header
#include "../../include/GameObject.h"
#include "../../include/SnakeObject.h"
#include "../../include/Tag.h"
#include "../../include/SceneManager.h"

#include <unordered_map>
#include <vector>
#include <cmath>

// Constructor for GameScene
GameScene::GameScene(SceneManager& sceneManager) : Scene(sceneManager), sceneManager(sceneManager){ 
    // Initialize any game-specific resources or variables here if needed
  initializeBoard();
  initializeGameObjects();
}

void GameScene::start() {

}

void GameScene::eventPoller(sf::RenderWindow &window) {
  tappedKeyMapping.clear();
  while (window.pollEvent(event)){
    if (event.type == sf::Event::EventType::Closed)
      window.close();
    else if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased){
      if(event.type == sf::Event::EventType::KeyPressed){
        tappedKeyMapping[event.key.code] = true;
      }
      keyMap[event.key.code] = event.type == sf::Event::EventType::KeyPressed ? true : false;
    }
  }
}

// Implementation of handleInput for GameScene
void GameScene::inputHandler() {
  if(tappedKeyMapping[sf::Keyboard::Key::Enter]){
    addBody = true;
  }
  if(tappedKeyMapping[sf::Keyboard::Key::W]){
    moveDir = sf::Vector2f(0, -1);
    moveInput = true;
  }
  else if(tappedKeyMapping[sf::Keyboard::Key::S]){
    moveDir = sf::Vector2f(0, 1);
    moveInput = true;
  }
  else if(tappedKeyMapping[sf::Keyboard::Key::A]){
    moveDir = sf::Vector2f(-1, 0);
    moveInput = true;
  }
  else if(tappedKeyMapping[sf::Keyboard::Key::D]){
    moveDir = sf::Vector2f(1, 0);
    moveInput = true;
  }
}

void GameScene::update(sf::RenderWindow &window) {
  deltaTime = clock.getElapsedTime().asSeconds();
  collisionCheck();
  if(addBody){
    snakeObject->addBody();
    addBody = false;
  }
  if(moveInput){
    snakeObject->newMove(moveDir, snakeObject->snakeHead->getAbsLoc());
    moveInput = false;
  }
  snakeObject->updateMove(deltaTime);
  clock.restart();
  // a->setPosition(a->getPosition() + sf::Vector2f(40, 0)*deltaTime);
  // b->move(sf::Vector2f(40, 0)*deltaTime);


  clock.restart();
}

void GameScene::render(sf::RenderWindow &window) {
  window.clear();
  renderedGameObjects.clear();

  for (GameObject* g : allGameObjects){
    g->render(renderedGameObjects);
  }

  std::sort(renderedGameObjects.begin(), renderedGameObjects.end(), GameObject::compareByZIndex);

  for(GameObject* g : renderedGameObjects){
    window.draw(g->getCircleShape());
  }

  window.draw(*a);
  window.draw(*b);
  window.display();
}

void GameScene::initializeGameObjects(){
  snakeObject = new SnakeObject();
  snakeObject->setShouldRender(true);

  a = new sf::CircleShape(20);
  b = new sf::CircleShape(20);
  a->setPosition(0, 0);
  b->setPosition(0, 40);
  allGameObjects.push_back(snakeObject);
}

void GameScene::collisionCheck(){
  sf::FloatRect snakeHeadGlobalBounds = snakeObject->snakeHead->getCircleShape().getGlobalBounds();
  for(int i=2; i<snakeObject->snakeBodies.size(); i++){
    GameObject* it = snakeObject->snakeBodies[i];
    if(snakeHeadGlobalBounds.intersects(it->getCircleShape().getGlobalBounds())){
      sf::Vector2f nextLoc = GameObject::getNextLocation(snakeObject->snakeHead->getAbsLoc(), snakeObject->snakeHead->getCurDir());
      sf::Vector2f targetNextLoc = GameObject::getNextLocation(it->getAbsLoc(), it->getCurDir());
      sf::Vector2f targetLastLoc = it->getLastLocation();
      float a = pow(targetNextLoc.x - nextLoc.x, 2) + pow(targetNextLoc.y - nextLoc.y, 2);
      float b = pow(targetLastLoc.x - nextLoc.x, 2) + pow(targetLastLoc.y - nextLoc.y, 2);
      float c = pow(targetNextLoc.x - targetLastLoc.x, 2) + pow(targetNextLoc.y - targetLastLoc.y, 2);
      if(a+b-c < 1e-9){
        endGame();
      }
    }
  }
}

void GameScene::initializeBoard(){
  board = new sf::RectangleShape(sf::Vector2f(columns*cellSize, rows*cellSize));
  backGroundSprites.push_back(board);
}

void GameScene::endGame(){
  sceneManager.changeScene(new EndScene(sceneManager));
}

// void GameScene::updateBoard(sf::RenderWindow &window){
//   board->
// }
