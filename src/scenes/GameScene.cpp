// Include necessary headers
#include "GameScene.h"

#include "../../include/Scene.h" // Include the base class header
#include "../../include/GameObject.h"

#include <unordered_map>
#include <vector>

// Constructor for GameScene
GameScene::GameScene() {
    // Initialize any game-specific resources or variables here if needed
}

void GameScene::start() {

}

void GameScene::eventPoller(sf::RenderWindow &window, sf::Event &event) {
  tappedKeyMapping.clear();
  while (window.pollEvent(event)){
    if (event.type == sf::Event::EventType::Closed)
      window.close();
    else{
      handleInput(window, event);
    }
  }
}

// Implementation of handleInput for GameScene
void GameScene::handleInput(sf::RenderWindow &window, sf::Event &event) {
  if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased){
    if(event.type == sf::Event::EventType::KeyPressed){
      tappedKeyMapping[event.key.code] = true;
    }
    keyMap[event.key.code] = event.type == sf::Event::EventType::KeyPressed ? true : false;
    std::cout << event.key.code << std::endl;
  }
}

// Implementation of update for GameScene
void GameScene::update() {
  deltaTime = clock.getElapsedTime().asSeconds();


  clock.restart();
    // Update logic specific to the game scene
    // ...
}

// Implementation of render for GameScene
void GameScene::render(sf::RenderWindow &window) {
  window.clear();

  window.display();
}
