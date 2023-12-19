// Include necessary headers
#include "../../include/GameScene.h"

#include "../../include/EndScene.h"
#include "../../include/Scene.h" // Include the base class header
#include "../../include/GameObject.h"
#include "../../include/SnakeObject.h"
#include "../../include/Tag.h"
#include "../../include/SceneManager.h"
#include "../../include/FontManager.h"
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

GameScene::GameScene(SceneManager& sceneManager) : Scene(sceneManager), sceneManager(sceneManager){ 
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GameScene::start() {
  initializeBoard(); // setting up the background of the game
  initializeText(); // loading fonts and the score
  initializeGameObjects(); // setting up the actual snakeobject
  spriteManager.setBoard(startX, startY, columns, rows, cellSize); // passing paramenters to the sprite manager
  spriteManager.setSnakeObject(snakeObject);
  spriteManager.spawnApple(); // spawning apples
  spriteManager.reset(); // setting the score to 0
  clock.restart(); //restarting the clock to 0
}

void GameScene::eventPoller() {
  tappedKeyMapping.clear();
  while (window->pollEvent(event)){
    if (event.type == sf::Event::EventType::Closed)
      window->close();
    else if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased){
      if(event.type == sf::Event::EventType::KeyPressed){
        tappedKeyMapping[event.key.code] = true;
      }
      keyMap[event.key.code] = event.type == sf::Event::EventType::KeyPressed ? true : false;
    }
  }
}

// Setting the direction of the snake
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

void GameScene::update() {
  if(gameEnded == true){
    return;
  }
  // std::cout << snakeObject->snakeHead->getAbsLoc().x << std::endl;
  // std::cout << snakeObject->snakeHead->getAbsLoc().y<< std::endl;
  deltaTime = clock.getElapsedTime().asSeconds();
  collisionCheck();
  
  // If there's a change in movement then we register it in
  if(moveInput){
    snakeObject->newMove(moveDir, snakeObject->snakeHead->getAbsLoc());
    moveInput = false;
  }
  // Otherwise we move the snake with the time that has passed
  snakeObject->updateMove(deltaTime);
  clock.restart();
}

void GameScene::render() {
  window->clear();
  renderedGameObjects.clear();

  for(sf::Sprite s : board){
    window->draw(s);
  }

  spriteManager.renderCurrentApple(*window);

  for (GameObject* g : allGameObjects){
    g->render(renderedGameObjects);
  }

  std::sort(renderedGameObjects.begin(), renderedGameObjects.end(), GameObject::compareByZIndex);

  for(GameObject* g : renderedGameObjects){
    window->draw(*(g->getCircleShape()));
  }

  window->draw(text[0]);

  if(gameEnded == true){
    window->draw(*filter);
    window->draw(text[1]);
  }

  window->display();
}

void GameScene::initializeGameObjects(){
  snakeObject = new SnakeObject(startX, startY, cellSize);
  snakeObject->setShouldRender(true);

  allGameObjects.push_back(snakeObject);
}

void GameScene::collisionCheck(){
  // snake hit body check
  sf::FloatRect snakeHeadGlobalBounds = snakeObject->snakeHead->getCircleShape()->getGlobalBounds();
  for(int i=2; i<snakeObject->snakeBodies.size(); i++){
    GameObject* it = snakeObject->snakeBodies[i];
    if(snakeHeadGlobalBounds.intersects(it->getCircleShape()->getGlobalBounds())){
      sf::Vector2f nextLoc = GameObject::getNextLocation(snakeObject->snakeHead->getAbsLoc(), snakeObject->snakeHead->getCurDir(), startX, startY, cellSize);
      sf::Vector2f targetNextLoc = GameObject::getNextLocation(it->getAbsLoc(), it->getCurDir(), startX, startY, cellSize);
      sf::Vector2f targetLastLoc = it->getLastLocation();
      float a = pow(targetNextLoc.x - nextLoc.x, 2) + pow(targetNextLoc.y - nextLoc.y, 2);
      float b = pow(targetLastLoc.x - nextLoc.x, 2) + pow(targetLastLoc.y - nextLoc.y, 2);
      float c = pow(targetNextLoc.x - targetLastLoc.x, 2) + pow(targetNextLoc.y - targetLastLoc.y, 2);
      if(a+b-c < 1e-9){
        endGame();
      }
    }
  }

  // snake hit apple check
  if(spriteManager.getCurrentApple() != nullptr && snakeHeadGlobalBounds.intersects(spriteManager.getCurrentApple()->getCircleShape()->getGlobalBounds())){
    if(snakeObject->snakeHead->getCurDir().x == 1){
      if(snakeObject->snakeHead->getAbsLoc().x >= spriteManager.getCurrentApple()->getAbsLoc().x){
        spriteManager.eatApple(snakeObject);
        updateScore();
      }
    }
    else if(snakeObject->snakeHead->getCurDir().x == -1){
      if(snakeObject->snakeHead->getAbsLoc().x <= spriteManager.getCurrentApple()->getAbsLoc().x){
        spriteManager.eatApple(snakeObject);
        updateScore();
      }
    }
    else if(snakeObject->snakeHead->getCurDir().y == 1){
      if(snakeObject->snakeHead->getAbsLoc().y >= spriteManager.getCurrentApple()->getAbsLoc().y){
        spriteManager.eatApple(snakeObject);
        updateScore();
      }
    }
    else {
      if(snakeObject->snakeHead->getAbsLoc().y <= spriteManager.getCurrentApple()->getAbsLoc().y){
        spriteManager.eatApple(snakeObject);
        updateScore();
      }
    }
  }

  //snake hit edge check

  if(snakeObject->snakeHead->getCurDir().x == 1){
    if(snakeObject->snakeHead->getAbsLoc().x + cellSize/2 * snakeObject->snakeHead->getCurDir().x > endX){

      endGame();
    }
  }
  else if(snakeObject->snakeHead->getCurDir().x == -1){
    if(snakeObject->snakeHead->getAbsLoc().x + cellSize/2 * snakeObject->snakeHead->getCurDir().x < startX){
      endGame();
    }
  }
  else if(snakeObject->snakeHead->getCurDir().y == 1){
     if(snakeObject->snakeHead->getAbsLoc().y + cellSize/2 * snakeObject->snakeHead->getCurDir().y > endY){
      endGame();
    }
  }
  else {
    if(snakeObject->snakeHead->getAbsLoc().y + cellSize/2 * snakeObject->snakeHead->getCurDir().y < startY){
      endGame();
    }
  }
}

void GameScene::initializeBoard(){
  // board = new sf::RectangleShape(sf::Vector2f(columns*cellSize, rows*cellSize));
  textures.push_back(new sf::Texture());
  textures.push_back(new sf::Texture());
  textures[0]->loadFromFile("../sprites/tiles/middle/tile217.png");
  textures[1]->loadFromFile("../sprites/tiles/middle/tile218.png");

  

  sceneManager.getRenderWindow();

  float middleX = window->getSize().x/2;
  float middleY = window->getSize().y/2;
  startX = middleX - columns * cellSize / 2;
  startY = middleY - rows * cellSize / 2;

  endX = columns*cellSize + startX;
  endY = rows*cellSize + startY;

  for(int i = 0; i<columns; i++){
    for(int j = 0; j<rows; j++){
      board.push_back(sf::Sprite());
      int chance = std::rand() % 4;
      if(chance == 0){
        board.back().setTexture(*textures[0]);
      }
      else{
        board.back().setTexture(*textures[1]);
      }
      board.back().setPosition(startX + i*cellSize, startY + j*cellSize);
      board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
    }
  }


  // The rest of this is the background for the board of the game. It can be ignored
  // top left
  textures.push_back(new sf::Texture());
  textures[2]->loadFromFile("../sprites/tiles/top left/tile048.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[2]);
  board.back().setPosition(startX - 2 * cellSize, startY - 2 * cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[3]->loadFromFile("../sprites/tiles/top left/tile049.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[3]);
  board.back().setPosition(startX - cellSize, startY - 2 * cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[4]->loadFromFile("../sprites/tiles/top left/tile064.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[4]);
  board.back().setPosition(startX - 2 * cellSize, startY - cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[5]->loadFromFile("../sprites/tiles/top left/tile065.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[5]);
  board.back().setPosition(startX - cellSize, startY - cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  //top right
  textures.push_back(new sf::Texture());
  textures[6]->loadFromFile("../sprites/tiles/top right/tile055.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[6]);
  board.back().setPosition(endX + cellSize, startY - 2 * cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[7]->loadFromFile("../sprites/tiles/top right/tile054.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[7]);
  board.back().setPosition(endX, startY - 2 * cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[8]->loadFromFile("../sprites/tiles/top right/tile071.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[8]);
  board.back().setPosition(endX + cellSize, startY - cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[9]->loadFromFile("../sprites/tiles/top right/tile070.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[9]);
  board.back().setPosition(endX, startY - cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  //bottom right
  textures.push_back(new sf::Texture());
  textures[10]->loadFromFile("../sprites/tiles/bottom right/tile167.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[10]);
  board.back().setPosition(endX + cellSize, endY + cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[11]->loadFromFile("../sprites/tiles/bottom right/tile166.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[11]);
  board.back().setPosition(endX, endY + cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[12]->loadFromFile("../sprites/tiles/bottom right/tile151.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[12]);
  board.back().setPosition(endX + cellSize, endY);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[13]->loadFromFile("../sprites/tiles/bottom right/tile150.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[13]);
  board.back().setPosition(endX, endY);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  // bottom left
  textures.push_back(new sf::Texture());
  textures[14]->loadFromFile("../sprites/tiles/bottom left/tile160.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[14]);
  board.back().setPosition(startX - 2 * cellSize, endY + cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[15]->loadFromFile("../sprites/tiles/bottom left/tile161.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[15]);
  board.back().setPosition(startX - cellSize, endY + cellSize);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[16]->loadFromFile("../sprites/tiles/bottom left/tile144.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[16]);
  board.back().setPosition(startX - 2 * cellSize, endY);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  textures.push_back(new sf::Texture());
  textures[17]->loadFromFile("../sprites/tiles/bottom left/tile145.png");
  board.push_back(sf::Sprite());
  board.back().setTexture(*textures[17]);
  board.back().setPosition(startX - cellSize, endY);
  board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

  textures.push_back(new sf::Texture());
  textures[18]->loadFromFile("../sprites/tiles/top/tile050.png");
  textures.push_back(new sf::Texture());
  textures[19]->loadFromFile("../sprites/tiles/top/tile066.png");
  textures.push_back(new sf::Texture());
  textures[20]->loadFromFile("../sprites/tiles/bottom/tile162.png");
  textures.push_back(new sf::Texture());
  textures[21]->loadFromFile("../sprites/tiles/bottom/tile146.png");
  for(int i = 0; i<columns; i++){
    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[18]);
    board.back().setPosition(startX + i * cellSize, startY - 2 * cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[19]);
    board.back().setPosition(startX + i * cellSize, startY - cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[20]);
    board.back().setPosition(startX + i * cellSize, endY +  cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[21]);
    board.back().setPosition(startX + i * cellSize, endY);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  }


  textures.push_back(new sf::Texture());
  textures[22]->loadFromFile("../sprites/tiles/left/tile080.png");
  textures.push_back(new sf::Texture());
  textures[23]->loadFromFile("../sprites/tiles/left/tile081.png");
  textures.push_back(new sf::Texture());
  textures[24]->loadFromFile("../sprites/tiles/right/tile086.png");
  textures.push_back(new sf::Texture());
  textures[25]->loadFromFile("../sprites/tiles/right/tile087.png");
  for(int i = 0; i<rows; i++){
    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[22]);
    board.back().setPosition(startX - 2 * cellSize, startY + i * cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[23]);
    board.back().setPosition(startX - cellSize, startY + i * cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[24]);
    board.back().setPosition(endX, startY + i * cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);

    board.push_back(sf::Sprite());
    board.back().setTexture(*textures[25]);
    board.back().setPosition(endX + cellSize, startY + i * cellSize);
    board.back().scale(cellSize / board.back().getLocalBounds().width, cellSize / board.back().getLocalBounds().height);
  }
}

// Ends the game
void GameScene::endGame(){
  gameEnded = true;
}

void GameScene::initializeText(){
  fonts["Melted Monster"] = fontManager.getFont("../fonts/Melted Monster.ttf");
  text.push_back(FontManager::addText("0", &fonts["Melted Monster"], 24, sf::Vector2f(20, 20)));
  fonts["NightsideDemoRegular.ttf"] = fontManager.getFont("../fonts/NightsideDemoRegular.ttf");
  text.push_back(FontManager::addText("GAME OVER", &fonts["NightsideDemoRegular.ttf"], 100, sf::Vector2f(window->getSize().x/2, window->getSize().y/2)));
  text[1].setOrigin(text[1].getLocalBounds().getSize().x/2, text[1].getLocalBounds().getSize().y/2);
  filter = new sf::RectangleShape(sf::Vector2f(window->getSize().x, window->getSize().y));
  filter->setFillColor(sf::Color(255, 0, 0, 128));
}

void GameScene::updateScore(){
  text[0].setString(std::to_string(spriteManager.getScore()));
}