#include "MazeSolver.h"

auto MazeSolver::neighbours(Coordinates tile) -> std::vector<Coordinates>
{
	std::vector<Coordinates> neighbours;

	if (tile.first > 0 && !maze[index(tile.first - 1, tile.second)])
		neighbours.emplace_back(Coordinates(tile.first - 1, tile.second));
	if (tile.second < width - 1 && !maze[index(tile.first, tile.second + 1)])
		neighbours.emplace_back(Coordinates(tile.first, tile.second + 1));
	if (tile.first < height - 1 && !maze[index(tile.first + 1, tile.second)])
		neighbours.emplace_back(Coordinates(tile.first + 1, tile.second));
	if (tile.second > 0 && !maze[index(tile.first, tile.second + 1)])
		neighbours.emplace_back(Coordinates(tile.first, tile.second - 1));

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
	std::unordered_map<Coordinates, bool> visited;
	for (unsigned int row = 0; row < height; row++)
		for (unsigned int column = 0; column < width; column++)
			visited[Coordinates(row, column)] = false;
	std::unordered_map<Coordinates, Coordinates> cameFrom;
	std::queue<Coordinates> queue;
	unsigned int length = 0;

	bool goalReached = false;
	Coordinates current = start;
	queue.push(current);
	visited[current] = true;
	cameFrom[current] = current;
	while (!queue.empty())
	{
		current = queue.front();
		queue.pop();
		for (auto neighbour : neighbours(current))
		{
			if (!visited[neighbour])
			{
				cameFrom[neighbour] = current;
				queue.push(neighbour);
				visited[neighbour] = true;
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
	Coordinates prev = cameFrom[goal];
	do
	{
		++length;
		path.emplace_back(prev);
		prev = cameFrom[prev];
	} while (prev != cameFrom[prev]);
	std::reverse(path.begin(), path.end());
	for (auto tile : path)
		sf::err() << "[" << tile.first << "][" << tile.second << "] ->";
	sf::err() << "\n";
	return Solution(length, path);
}

MazeSolver::MazeSolver(unsigned width, unsigned height)
	: MazePrimitive(width, height) { }
