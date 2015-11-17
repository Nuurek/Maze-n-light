#include "Tile.h"



void Tile::draw(sf::RenderWindow & window, float deltaTime)
{
	animationHandler.changeAnimation(tileType);
	animationHandler.update(deltaTime);
	sprite.setTextureRect(animationHandler.bounds);
	window.draw(sprite);
}

Tile::Tile(bool collision, sf::Texture& texture, const std::vector<Animation>& animations)
	: makeCollision(collision) 
{
	sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite.setTexture(texture);
	animationHandler.frameSize = sf::IntRect(0, 0, frameSize, frameSize);
	for (auto animation : animations)
		animationHandler.addAnim(animation);
	animationHandler.update(0.0f);
}