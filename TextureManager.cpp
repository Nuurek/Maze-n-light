#include "TextureManager.h"



void TextureManager::loadTexture(const std::string & name, const std::string & filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);
	textures[name] = texture;
}

sf::Texture & TextureManager::getTexture(const std::string & texture)
{
	return textures[texture];
}

TextureManager::TextureManager()
{
}
