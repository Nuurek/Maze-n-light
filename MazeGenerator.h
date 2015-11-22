#pragma once
#include <random>
#include <array>
#include <chrono>
#include <algorithm>

#include "MazePrimitive.h"
#include "Directions.h"

class MazeGenerator : MazePrimitive<char>
{
	//Random engine. Mersene Twister by default IIRC.
	std::default_random_engine _randomEngine;
	//Generates random direction's order of the recursion.
	std::array<Directions, 4> generateRandomDirections();
	//Source of the maze generation. Uses DFS.
	void recursion(unsigned int row, unsigned int column);
	
public:
	//Generates new vector of chars describing maze.
	//0 - tunnel, 1 - wall.
	std::vector<char> generateMaze();
	//Gives back coordinates of a randomly generated exit on the loaded labyrinth.
	Coordinates getRandomExit();

	MazeGenerator(unsigned int width, unsigned int height);
};

