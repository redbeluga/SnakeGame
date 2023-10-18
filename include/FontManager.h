#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class FontManager {
  public:
    // Function to get the singleton instance
    static FontManager& getInstance();

    // Function to get a font by filename
    sf::Font& getFont(const std::string& filename);

  private:
    FontManager(); // Private constructor to prevent external instantiation
    FontManager(const FontManager&) = delete; // Disable copy constructor
    FontManager& operator=(const FontManager&) = delete; // Disable assignment operator

    std::map<std::string, sf::Font> fonts;
};

#endif
