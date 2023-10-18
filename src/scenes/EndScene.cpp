#include "../../include/EndScene.h"


EndScene::EndScene(SceneManager& sceneManager) : Scene(sceneManager), sceneManager(sceneManager){ 
}
void EndScene::start() {

}

void EndScene::eventPoller(sf::RenderWindow &window) {
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

void EndScene::inputHandler() {
}

void EndScene::update(sf::RenderWindow &window) {
}

void EndScene::render(sf::RenderWindow &window) {
  window.clear();
  window.display();
}