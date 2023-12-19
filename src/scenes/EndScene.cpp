#include "../../include/EndScene.h"

// We planned to use this but it was not used in the end
// Scene used after snake dies

EndScene::EndScene(SceneManager& sceneManager) : Scene(sceneManager), sceneManager(sceneManager){
   
}

void EndScene::start() {

}

void EndScene::eventPoller() {
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

void EndScene::inputHandler() {
}

void EndScene::update() {
}

void EndScene::render() {
  window->clear();
  window->display();
}