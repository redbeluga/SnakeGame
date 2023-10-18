#include "../../include/FontManager.h"

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

