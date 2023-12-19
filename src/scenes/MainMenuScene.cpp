#include "../../include/MainMenuScene.h"

#include <iostream>

MainMenuScene::MainMenuScene(SceneManager& sceneManager) : Scene(sceneManager), sceneManager(sceneManager){
}

void MainMenuScene::start() {
  // Grab necessary fonts
  fonts["Nightside"] = fontManager.getFont("../fonts/NightsideDemoRegular.ttf");
  titleTexture.loadFromFile("../sprites/title.png");
  titleTexture.setSmooth(true);
  
  // setup sprites for the background 
  titleSprite.setTexture(titleTexture);
  titleSprite.setPosition(50, 150);
  backGroundSprites.push_back(titleSprite);

  backgroundText.push_back(FontManager::addText("Play", &fonts["Nightside"], 24, sf::Vector2f(200, 450)));
  backgroundText.push_back(FontManager::addText("Settings", &fonts["Nightside"], 24, sf::Vector2f(200, 500)));
  backgroundText.push_back(FontManager::addText("Credits", &fonts["Nightside"], 24, sf::Vector2f(200, 550)));

  letterHighlightTexture.loadFromFile("../sprites/highlight.png");
  letterHighlightSprite.setTexture(letterHighlightTexture);
  letterHighlightSprite.setOrigin((sf::Vector2f)letterHighlightTexture.getSize() / 2.f);
  letterHighlightSprite.rotate(180);
  letterHighlightSprite.setPosition(sf::Vector2f(backgroundText[selected].getGlobalBounds().left-10, backgroundText[selected].getPosition().y));
  backGroundSprites.push_back(letterHighlightSprite);
}

void MainMenuScene::eventPoller() {
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

// This is used to change the selection between "start game", "options", and "credits"

void MainMenuScene::inputHandler() {
  switchScenes = false;
  if(tappedKeyMapping[sf::Keyboard::Key::Enter]){
    std::cout << 1 << std::endl;
    switchScenes = true;
  }
  if(tappedKeyMapping[sf::Keyboard::Key::Down]){
    selected = (selected + 1) % 3;
    // std::cout << selected << std::endl;
    changeSelection();
  }
  else if(tappedKeyMapping[sf::Keyboard::Up]){
    selected = (selected - 1 < 0) ? 2 : selected - 1;
    // std::cout << selected << std::endl;
    changeSelection();
  }
}

void MainMenuScene::changeSelection(){
  backGroundSprites.pop_back();
  int gap = 15;
  letterHighlightSprite.setPosition(sf::Vector2f(backgroundText[selected].getGlobalBounds().left - gap, backgroundText[selected].getPosition().y));
  backGroundSprites.push_back(letterHighlightSprite);
}

void MainMenuScene::update() {
}

void MainMenuScene::render() {
  window->clear();

  if(switchScenes){
    if(selected == 0){
      sceneManager.changeScene(0);
    }
    else if(selected == 1){

    }
  }
  for(auto s : backGroundSprites){
    window->draw(s);
  }
  for(auto t : backgroundText){
    window->draw(t);
  }

  window->display();
}