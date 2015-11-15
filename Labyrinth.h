#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "MazePrimitive.h"
#include "Tile.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "TextureManager.h"

class Labyrinth : public MazePrimitive<Tile>
{
	void updateTileTypes();

public:
	std::vector<Tile>& tiles = maze;
	Coordinates exit;

	const unsigned int tileSize = 48;

	void solveMaze();

	void draw(sf::RenderWindow& window, float deltaTime);
	Labyrinth(unsigned int width, unsigned int height, TextureManager& textureManager, 
		std::map<std::string, Tile>& tileAtlas);
};

