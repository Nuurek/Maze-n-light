#pragma once
#include <SFML\Graphics.hpp>

#include "AnimationHandler.h"

//Tile type available in game.
enum class TileType
{
	Tunnel, Wall, Exit
};

class Tile
{
	//TODO: animated tiles.
	AnimationHandler animationHandler;

public:
	//Tile's size in pixels.
	static const unsigned int frameSize = 48;
	
	sf::Sprite sprite;
	//Does tile make collision?
	bool makeCollision;
	//Orientation of the tile that depends on the neighbour tiles. Sprite of the tile uses it.
	//16 varius orientations.
	unsigned int orientation;
	//Type of the tile: Tunnel, Wall, Exit.
	TileType tileType;
	
	void draw(sf::RenderWindow& window, float deltaTime);

	Tile() {}
	Tile(TileType type, bool collision, sf::Texture& texture, const std::vector<Animation>& animations);
};

