#pragma once
#include <string>
#include <map>
#include "SFML/Graphics.hpp"

//Class that maps textures to std::strings for easier use.
class TextureManager
{
	std::map<std::string, sf::Texture> textures;

public:
	void loadTexture(const std::string& name, const std::string& filename);

	sf::Texture& getTexture(const std::string& texture);

	TextureManager();
};

