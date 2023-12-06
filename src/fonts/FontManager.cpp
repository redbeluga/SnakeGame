#include "../../include/FontManager.h"

#include <string>
#include <iostream>

FontManager::FontManager() {
    // Constructor implementation, if needed
}

FontManager& FontManager::getInstance() {
    static FontManager instance; // Static instance of the FontManager
    return instance;
}

sf::Font& FontManager::getFont(const std::string& filename) {
    if (fonts.find(filename) == fonts.end()) {
        sf::Font font;
        if (font.loadFromFile(filename)) {
            fonts[filename] = font;
        }
        // Handle font loading errors if needed
    }
    return fonts[filename];
}

sf::Text FontManager::addText(std::string content, sf::Font* font, int characterSize, sf::Vector2f position){
  sf::Text text;
  text.setFont(*font);
  text.setPosition(position);
  text.setCharacterSize(characterSize);
  text.setString(content);
  text.setOrigin(0, text.getLocalBounds().height / 2.f);
  return text;
}

