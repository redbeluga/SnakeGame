#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "SceneManager.h"
#include "Scene.h" 

#include <unordered_map>
#include <vector>

class EndScene : public Scene{
  protected:
    SceneManager& sceneManager;
  private:
    std::unordered_map<int, bool> keyMap;
    std::unordered_map<int, bool> tappedKeyMapping;
    
        // Event Poller
    sf::Event event;

  public:
    EndScene(SceneManager& sceneManager); // Constructor
    virtual void start() override;
    virtual void inputHandler() override;
    virtual void update() override;
    virtual void render() override;
    virtual void eventPoller() override;
    // void updateBoard(sf::RenderWindow &window);
};

#endif