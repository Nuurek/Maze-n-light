#pragma once
#include <random>
#include <array>
#include <chrono>
#include <algorithm>

#include "MazePrimitive.h"
#include "Directions.h"

class MazeGenerator : MazePrimitive<char>
{
	std::default_random_engine _randomEngine;
	std::array<Directions, 4> generateRandomDirections();
	void recursion(unsigned int row, unsigned int column);
	
public:
	std::vector<char> generateMaze();
	Coordinates getRandomExit();

	MazeGenerator(unsigned int width, unsigned int height);
};

