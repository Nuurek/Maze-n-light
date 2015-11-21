#include "Labyrinth.h"



void Labyrinth::updateTileTypes()
{
	std::array<bool, 4> walls{ 0, 0, 0, 0 };
	for (unsigned int row = 0; row < height; row++)
		for (unsigned int column = 0; column < width; column++)
		{
			walls = { 0, 0, 0, 0 };
			Tile& tile = tiles[index(row, column)];
			if (tile.makeCollision)
			{
				if (row == 0 || !tiles[index(row - 1, column)].makeCollision)
					walls[static_cast<unsigned int>(Directions::Up)] = true;
				if (column == width - 1 || !tiles[index(row, column + 1)].makeCollision)
					walls[static_cast<unsigned int>(Directions::Right)] = true;
				if (row == height - 1 || !tiles[index(row + 1, column)].makeCollision)
					walls[static_cast<unsigned int>(Directions::Down)] = true;
				if (column == 0 || !tiles[index(row, column - 1)].makeCollision)
					walls[static_cast<unsigned int>(Directions::Left)] = true;

				if (walls[0] && walls[1] && walls[2] && walls[3])
					tile.orientation = 0;

				else if (walls[1] && walls[2] && walls[3])
					tile.orientation = 1;
				else if (walls[0] && walls[2] && walls[3])
					tile.orientation = 2;
				else if (walls[0] && walls[1] && walls[3])
					tile.orientation = 3;
				else if (walls[0] && walls[1] && walls[2])
					tile.orientation = 4;

				else if (walls[2] && walls[3])
					tile.orientation = 5;
				else if (walls[0] && walls[3])
					tile.orientation = 6;
				else if (walls[0] && walls[1])
					tile.orientation = 7;
				else if (walls[1] && walls[2])
					tile.orientation = 8;
				else if (walls[1] && walls[3])
					tile.orientation = 9;
				else if (walls[0] && walls[2])
					tile.orientation = 10;

				else if (walls[3])
					tile.orientation = 11;
				else if (walls[0])
					tile.orientation = 12;
				else if (walls[1])
					tile.orientation = 13;
				else if (walls[2])
					tile.orientation = 14;

				else
					tile.orientation = 15;
			}
			else tile.orientation = 0;
		}
}

void Labyrinth::solveMaze()
{
	MazeSolver solver(width, height);
	solver.loadLabyrinth(*this);
	std::pair<unsigned int, std::vector<Coordinates>> solution = solver.solveMaze(Coordinates(width / 2, height /2), exit);
	shortestPathLength = solution.first + 1;
}

void Labyrinth::draw(sf::RenderWindow & window, float deltaTime)
{
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			sf::Vector2f position;
			position.x = static_cast<float>(x * Tile::frameSize);
			position.y = static_cast<float>(y * Tile::frameSize);
			tiles[y * width + x].sprite.setPosition(position);
			tiles[y * width + x].draw(window, deltaTime);
		}
	}

}

Labyrinth::Labyrinth(std::string filename, TextureManager & textureManager, std::map<std::string, Tile>& tileAtlas)
{
	std::ifstream file(filename, std::ios::in);
	unsigned int newWidth, newHeight;
	file >> std::string() >> newWidth >> newHeight >> std::string() >> newWidth >> newHeight;

	width = newWidth;
	height = newHeight;

	unsigned int tileType, orientation;

	tiles.clear();
	for (unsigned int row = 0; row < height; row++)
	{
		for (unsigned int column = 0; column < width; column++)
		{
			file >> tileType >> orientation;
			unsigned int id = index(row, column);
			switch (tileType)
			{
				case (0) :
					tiles.emplace_back(tileAtlas.at("tunnel"));
					tiles[id].orientation = 0;
					break;
				case (1) :
					tiles.emplace_back(tileAtlas.at("wall"));
					tiles[id].orientation = orientation;
					break;
				case (2) :
					tiles.emplace_back(tileAtlas.at("exit"));
					tiles[id].orientation = 0;
					exit = sf::Vector2u(row, column);
					break;
			}
		}
	}
	solveMaze();
}

Labyrinth::Labyrinth(unsigned int width, unsigned int height, TextureManager& textureManager,
	std::map<std::string, Tile>& tileAtlas)
	: MazePrimitive(width, height)
{
	MazeGenerator generator(width, height);
	auto maze = generator.generateMaze();

	tiles.clear();
	for (auto tile : maze)
	{
		if (tile == 0)
			tiles.emplace_back(tileAtlas.at("tunnel"));
		else if (tile == 1)
			tiles.emplace_back(tileAtlas.at("wall"));
	}
	exit = generator.getRandomExit();
	tiles.at(index(exit.x, exit.y)) = Tile(tileAtlas.at("exit"));
	updateTileTypes();
	solveMaze();
}
