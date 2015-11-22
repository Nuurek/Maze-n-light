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
	//Returns vector of coordinates of tiles neighobur to the given tile.
	std::vector<Coordinates>neighbours(Coordinates tile);

public:
	//Solution is represented by: length of the shortest path and
	//a vector of following tiles in the shortest path.
	using Solution = std::pair<unsigned int, std::vector<Coordinates>>;
	//Loads labyrinth into solver.
	void loadLabyrinth(Labyrinth& labyrinth);
	//Finds a solution from start to goal.
	Solution solveMaze(Coordinates start, Coordinates goal);

	MazeSolver(unsigned width, unsigned height);
};

