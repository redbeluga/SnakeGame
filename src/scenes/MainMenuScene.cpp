#include "../../include/MainMenuScene.h"

#include <iostream>

MainMenuScene::MainMenuScene(SceneManager& sceneManager) : Scene(sceneManager), sceneManager(sceneManager){
   start();
}
void MainMenuScene::start() {
  // Load Shit
  fonts["Nightside"] = fontManager.getFont("../fonts/NightsideDemoRegular.ttf");
  titleTexture.loadFromFile("../sprites/title.png");
  titleTexture.setSmooth(true);
  // std::cout << backGroundSprites.size() << std::endl;
  titleSprite.setTexture(titleTexture);
  titleSprite.setPosition(50, 150);
  backGroundSprites.push_back(titleSprite);

  backgroundText.push_back(FontManager::addText("Play", &fonts["Nightside"], 24, sf::Vector2f(200, 450)));
  backgroundText.push_back(FontManager::addText("Settings", &fonts["Nightside"], 24, sf::Vector2f(200, 500)));
  backgroundText.push_back(FontManager::addText("Credits", &fonts["Nightside"], 24, sf::Vector2f(200, 550)));

  letterHighlightTexture.loadFromFile("../sprites/highlight.png");
  letterHighlightSprite.setTexture(letterHighlightTexture);
  letterHighlightSprite.setOrigin((sf::Vector2f)letterHighlightTexture.getSize() / 2.f);
  // letterHighlightSprite.setPosition(sf::Vector2f(backgroundText[selected].getGlobalBounds().left+backgroundText[selected].getGlobalBounds().width + 10, backgroundText[selected].getPosition().y));
  // backGroundSprites.push_back(letterHighlightSprite);
  letterHighlightSprite.scale(-1.f, 1.f);
  letterHighlightSprite.setPosition(sf::Vector2f(backgroundText[selected].getGlobalBounds().left-10, backgroundText[selected].getPosition().y));
  backGroundSprites.push_back(letterHighlightSprite);
  // letterHighlightTexture.setSmooth(true);
  // letterHighlightSprite.setTexture(letterHighlightTexture);
  // letterHighlightSprite.setPosition(510, 402);
  // backGroundSprites.push_back(letterHighlightSprite);
  // letterHighlightSprite.setPosition(510, 447);
  // backGroundSprites.push_back(letterHighlightSprite);
  // letterHighlightSprite.setPosition(510, 492);
  // backGroundSprites.push_back(letterHighlightSprite);
  

  // std::cout << backGroundSprites.size() << std::endl;

  // std::cout << backGroundSprites.size() << std::endl;
}

void MainMenuScene::eventPoller(sf::RenderWindow &window) {
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

void MainMenuScene::inputHandler() {
  if(tappedKeyMapping[sf::Keyboard::Key::Enter]){
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
  // backGroundSprites.pop_back();
  int gap = 15;
  // letterHighlightSprite.scale(-1.f, 1.f);
  // letterHighlightSprite.setPosition(sf::Vector2f(backgroundText[selected].getGlobalBounds().left+backgroundText[selected].getGlobalBounds().width + gap, backgroundText[selected].getPosition().y));
  // backGroundSprites.push_back(letterHighlightSprite);
  // letterHighlightSprite.scale(-1.f, 1.f);
  letterHighlightSprite.setPosition(sf::Vector2f(backgroundText[selected].getGlobalBounds().left - gap, backgroundText[selected].getPosition().y));
  backGroundSprites.push_back(letterHighlightSprite);
}

void MainMenuScene::update(sf::RenderWindow &window) {
}

void MainMenuScene::render(sf::RenderWindow &window) {
  window.clear();

  if(switchScenes){
    if(selected == 0){
      sceneManager.changeScene(0);
    }
    else if(selected == 1){

    }
  }
  for(auto s : backGroundSprites){
    window.draw(s);
  }
  for(auto t : backgroundText){
    window.draw(t);
  }

  window.display();
}