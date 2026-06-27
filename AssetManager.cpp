#include "AssetManager.hpp"
#include <iostream>

void AssetManager::LoadTexture(const std::string& name, const std::string& fileName) {
    sf::Texture tex;
    if (tex.loadFromFile(fileName)) {
        _textures[name] = tex;
    } else {
        std::cerr << "Failed to load texture: " << fileName << std::endl;
    }
}

sf::Texture& AssetManager::GetTexture(const std::string& name) {
    return _textures.at(name);
}

void AssetManager::LoadFont(const std::string& name, const std::string& fileName) {
    sf::Font font;
    if (font.loadFromFile(fileName)) {
        _fonts[name] = font;
    } else {
        std::cerr << "Failed to load font: " << fileName << std::endl;
    }
}

sf::Font& AssetManager::GetFont(const std::string& name) {
    return _fonts.at(name);
}
