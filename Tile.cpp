#include "Tile.h"



void Tile::draw(sf::RenderWindow & window, float deltaTime)
{
	animationHandler.changeAnimation(orientation);
	animationHandler.update(deltaTime);
	sprite.setTextureRect(animationHandler.bounds);
	window.draw(sprite);
}

Tile::Tile(TileType type, bool collision, sf::Texture& texture, const std::vector<Animation>& animations)
	: tileType(type), makeCollision(collision) 
{
	sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite.setTexture(texture);
	animationHandler.frameSize = sf::IntRect(0, 0, frameSize, frameSize);
	for (auto animation : animations)
		animationHandler.addAnim(animation);
	animationHandler.update(0.0f);
}