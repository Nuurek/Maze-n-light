#pragma once
#include <SFML\Graphics.hpp>

#include "AnimationHandler.h"

enum class TileType
{
	Tunnel, Wall, Exit
};

class Tile
{
public:
	AnimationHandler animationHandler;
	sf::Sprite sprite;

	static const unsigned int frameSize = 48;
	bool makeCollision;
	unsigned int orientation;
	TileType tileType;
	
	void draw(sf::RenderWindow& window, float deltaTime);

	Tile() {}
	Tile(TileType type, bool collision, sf::Texture& texture, const std::vector<Animation>& animations);
};

