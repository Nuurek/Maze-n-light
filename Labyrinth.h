#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>

#include "MazePrimitive.h"
#include "Tile.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "TextureManager.h"

//Labyrinth class presents game representation of maze.
//Derives from MazePrimitive filling maze with Tiles.
//Uses MazeSolver to get the shortest solution path.
class Labyrinth : public MazePrimitive<Tile>
{
	//Tile's size in pixels. 
	const unsigned int tileSize = 48;
	//Updates every tile type - its orientation.
	void updateTileTypes();
	//Solves maze using MazeSolver.
	void solveMaze();

public:
	//Alias to vector of tiles.
	std::vector<Tile>& tiles = maze;
	//Coordinates to exit tile.
	Coordinates exit;
	//The best possible path on this labyrinth.
	unsigned int shortestPathLength;

	void draw(sf::RenderWindow& window, float deltaTime);
	Labyrinth() {};
	//Constructs labyrinth using savefile.
	//Texture manager and tile atlas used to load appropriate sprites.
	Labyrinth(std::string filename, TextureManager& textureManager,
		std::map<std::string, Tile>& tileAtlas);
	//Constructs labyrinth based on its dimensions.
	Labyrinth(unsigned int width, unsigned int height, TextureManager& textureManager, 
		std::map<std::string, Tile>& tileAtlas);
};

