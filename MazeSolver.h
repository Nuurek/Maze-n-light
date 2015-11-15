#pragma once
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include "MazePrimitive.h"
#include "Labyrinth.h"

class Labyrinth;

class MazeSolver :
	public MazePrimitive<char>
{
	std::vector<Coordinates>neighbours(Coordinates tile);

public:
	using Solution = std::pair<unsigned int, std::vector<Coordinates>>;

	void loadLabyrinth(Labyrinth& labyrinth);
	Solution solveMaze(Coordinates start, Coordinates goal);

	MazeSolver(unsigned width, unsigned height);
};

