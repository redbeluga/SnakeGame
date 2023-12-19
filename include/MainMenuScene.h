#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "FontManager.h"
#include "SceneManager.h"
#include "Scene.h" 

#include <unordered_map>
#include <vector>

class MainMenuScene : public Scene{
  protected:
    SceneManager& sceneManager;
  private:
    std::unordered_map<int, bool> keyMap;
    std::unordered_map<int, bool> tappedKeyMapping;

    std::vector<sf::Sprite> backGroundSprites;
    std::vector<sf::Text> backgroundText;
    sf::Texture letterHighlightTexture;
    sf::Sprite letterHighlightSprite;
    sf::Texture titleTexture;
    sf::Sprite titleSprite;

    FontManager& fontManager = FontManager::getInstance();

    std::map<std::string, sf::Font> fonts;

    int selected = 0;
    bool switchScenes = false;
    
        // Event Poller
    sf::Event event;

  public:
    MainMenuScene(SceneManager& sceneManager); // Constructor
    virtual void start() override;
    virtual void inputHandler() override;
    virtual void update() override;
    virtual void render() override;
    virtual void eventPoller() override;

    void changeSelection();
    // void updateBoard(sf::RenderWindow &window);
};

#endif