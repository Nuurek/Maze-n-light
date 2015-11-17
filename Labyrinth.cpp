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
					tile.tileType = 0;

				else if (walls[1] && walls[2] && walls[3])
					tile.tileType = 1;
				else if (walls[0] && walls[2] && walls[3])
					tile.tileType = 2;
				else if (walls[0] && walls[1] && walls[3])
					tile.tileType = 3;
				else if (walls[0] && walls[1] && walls[2])
					tile.tileType = 4;

				else if (walls[2] && walls[3])
					tile.tileType = 5;
				else if (walls[0] && walls[3])
					tile.tileType = 6;
				else if (walls[0] && walls[1])
					tile.tileType = 7;
				else if (walls[1] && walls[2])
					tile.tileType = 8;
				else if (walls[1] && walls[3])
					tile.tileType = 9;
				else if (walls[0] && walls[2])
					tile.tileType = 10;

				else if (walls[3])
					tile.tileType = 11;
				else if (walls[0])
					tile.tileType = 12;
				else if (walls[1])
					tile.tileType = 13;
				else if (walls[2])
					tile.tileType = 14;

				else
					tile.tileType = 15;
			}
			else tile.tileType = 0;
		}
}

void Labyrinth::solveMaze()
{
	MazeSolver solver(width, height);
	solver.loadLabyrinth(*this);
	std::pair<unsigned int, std::vector<Coordinates>> solution = solver.solveMaze(Coordinates(width / 2, height /2), exit);
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
			tiles.emplace_back(tileAtlas.at("corridor"));
		else if (tile == 1)
			tiles.emplace_back(tileAtlas.at("wall"));
	}
	exit = generator.getRandomExit();
	unsigned int id = index(exit.first, exit.second);
	tiles.at(id) = tileAtlas.at("exit");
	updateTileTypes();
}
