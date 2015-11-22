#include "MazeGenerator.h"



std::array<Directions, 4> MazeGenerator::generateRandomDirections()
{
	//Create array for four directions.
	std::array<Directions, 4> directions;
	//Insert directions in default order.
	for (unsigned int dir = 0; dir < 4; dir++)
	{
		directions[dir] = static_cast<Directions>(dir);
	}
	//Randomly shuffle the array.
	std::shuffle(directions.begin(), directions.end(), _randomEngine);
	return directions;
}

void MazeGenerator::recursion(unsigned int row, unsigned int column)
{
	//Generate random directions order for DFS.
	auto directions = generateRandomDirections();
	for (unsigned int direction = 0; direction < 4; direction++)
	{
		switch (static_cast<Directions>(directions[direction]))
		{
			//For every direction in which DFS would like to go, check whether it is possible:
			// - coordinates are in labyrinth
			// - tile which coordinates show is not tunnel
			//If it is possible break wall and run DFS from that tile.
			case Directions::Up:
			{
				if (row <= 2)
					continue;
				if (maze[index(row - 2, column)] != 0)
				{
					maze[index(row - 2, column)] = 0;
					maze[index(row - 1, column)] = 0;
					recursion(row - 2, column);
				}
				break;
			}
			case Directions::Right:
			{
				if (column >= width - 3)
					continue;
				if (maze[index(row, column + 2)] != 0)
				{
					maze[index(row, column + 2)] = 0;
					maze[index(row, column + 1)] = 0;
					recursion(row, column + 2);
				}
				break;
			}
			case Directions::Down:
			{
				if (row >= height - 3)
					continue;
				if (maze[index(row + 2, column)] != 0)
				{
					maze[index(row + 2, column)] = 0;
					maze[index(row + 1, column)] = 0;
					recursion(row + 2, column);
				}
				break;
			}
			case Directions::Left:
			{
				if (column <= 2)
					continue;
				if (maze[index(row, column - 2)] != 0)
				{
					maze[index(row, column - 2)] = 0;
					maze[index(row, column - 1)] = 0;
					recursion(row, column - 2);
				}
				break;
			}
		}
	}
}

std::vector<char> MazeGenerator::generateMaze()
{
	if (width % 2 == 0 || height % 2 == 0)
		return std::vector<char>();

	maze = std::vector<char>(width * height, 1);
	//Get a random start tile for algorithm.
	std::uniform_int_distribution<unsigned int> rowDistribution(1, height - 2);
	std::uniform_int_distribution<unsigned int> columnDistribution(1, width - 2);
	unsigned int row, column;
	do
	{
		row = rowDistribution(_randomEngine);
	} while (row % 2 == 0);
	do
	{
		column = columnDistribution(_randomEngine);
	} while (column % 2 == 0);

	maze[index(row, column)] = 0;
	//Start DFS.
	recursion(row, column);

	return maze;
}

auto MazeGenerator::getRandomExit() -> Coordinates
{
	//Get a random edge of the labyrinth in which the exit will be.
	std::uniform_int_distribution<unsigned int> distribution(0, 3);
	unsigned int edge = distribution(_randomEngine);
	unsigned int row, column;
	
	if (edge == 0)
		row = 0;
	else if (edge == 1)
		column = width - 1;
	else if (edge == 2)
		row = height - 1;
	else if (edge == 3)
		column = 0;
	//On this edge get a random tile that has connection with a tunnel.
	if (edge == 0 || edge == 2)
	{
		distribution = std::uniform_int_distribution<unsigned int>(1, width - 2);
		do
		{
			column = distribution(_randomEngine);
		} while ((edge == 0 && maze[index(row + 1, column)] == 1) || (edge == 2 && maze[index(row - 1, column)] == 1));
	}
	else if (edge == 1 || edge == 3)
	{
		distribution = std::uniform_int_distribution<unsigned int>(1, height - 2);
		do
		{
			row = distribution(_randomEngine);
		} while ((edge == 1 && maze[index(row, column - 1)] == 1) || (edge == 3 && maze[index(row, column + 1)] == 1));
	}

	maze[index(row, column)] = 0;

	return Coordinates(row, column);
}

MazeGenerator::MazeGenerator(unsigned int width, unsigned int height)
	: MazePrimitive(width, height)
{
	//Seed random engine with time.
	_randomEngine.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
}
