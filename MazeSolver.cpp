#include "MazeSolver.h"

std::vector<Coordinates> MazeSolver::neighbours(Coordinates tile)
{
	std::vector<Coordinates> neighbours;

	if (tile.x > 0 && !maze[index(tile.x - 1, tile.y)])
		neighbours.emplace_back(Coordinates(tile.x - 1, tile.y));
	if (tile.y < width - 1 && !maze[index(tile.x, tile.y + 1)])
		neighbours.emplace_back(Coordinates(tile.x, tile.y + 1));
	if (tile.x < height - 1 && !maze[index(tile.x + 1, tile.y)])
		neighbours.emplace_back(Coordinates(tile.x + 1, tile.y));
	if (tile.y > 0 && !maze[index(tile.x, tile.y - 1)])
		neighbours.emplace_back(Coordinates(tile.x, tile.y - 1));

	return neighbours;
}

void MazeSolver::loadLabyrinth(Labyrinth & labyrinth)
{
	maze.clear();
	for (auto tile : labyrinth.tiles)
		if (tile.makeCollision)
			maze.emplace_back(1);
		else
			maze.emplace_back(0);
}

auto MazeSolver::solveMaze(Coordinates start, Coordinates goal) -> Solution
{
	std::vector<bool> visited(width * height, false);
	std::unordered_map<unsigned int, unsigned int> cameFrom;
	std::queue<unsigned int> queue;
	unsigned int length = 0;

	bool goalReached = false;
	unsigned int startIndex = index(start.x, start.y);
	unsigned int goalIndex = index(goal.x, goal.y);
	unsigned int current = startIndex;
	queue.push(current);
	visited[current] = true;
	cameFrom[current] = current;
	while (!queue.empty())
	{
		current = queue.front();
		queue.pop();
		for (auto neighbour : neighbours(indexToCoordinates(current)))
		{
			unsigned int neighbourIndex = index(neighbour.x, neighbour.y);
			if (!visited[neighbourIndex])
			{
				cameFrom[neighbourIndex] = current;
				queue.push(neighbourIndex);
				visited[neighbourIndex] = true;
			}
			if (neighbour == goal)
			{
				goalReached = true;
				break;
			}
		}

		if (goalReached)
			break;
	}
	
	std::vector<Coordinates> path;
	path.emplace_back(goal);
	unsigned int prev = cameFrom[goalIndex];
	do
	{
		++length;
		path.emplace_back(indexToCoordinates(prev));
		prev = cameFrom[prev];
	} while (prev != cameFrom[prev]);

	std::reverse(path.begin(), path.end());
	
	return Solution(length, path);
}

MazeSolver::MazeSolver(unsigned width, unsigned height)
	: MazePrimitive(width, height) { }
