#include "GameState.h"

void GameState::draw(const float deltaTime)
{
	auto truePosition = player.truePosition();
	gameView.setCenter(truePosition.first, truePosition.second);
	game->window.setView(gameView);
	game->window.clear();
	game->window.draw(background);
	labyrinth.draw(game->window, deltaTime);
	player.draw(game->window, deltaTime);
}

void GameState::update(const float deltaTime)
{
	player.update(deltaTime);
}

void GameState::handleInput()
{
	sf::Event event;

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				game->window.close();
				break;
			}

			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					case (sf::Keyboard::Up) :
						player.move(Directions::Up);
						break;
					case (sf::Keyboard::Right) :
						player.move(Directions::Right);
						break;
					case (sf::Keyboard::Down) :
						player.move(Directions::Down);
						break;
					case (sf::Keyboard::Left) :
						player.move(Directions::Left);
						break;
					case (sf::Keyboard::Escape) :
						game->popState();
						break;
				}
			}
			default: 
			break;
		}
	}
}

GameState::GameState(std::shared_ptr<GameManager> game, unsigned int size)
	: labyrinth(Labyrinth(size, size, game->textureManager, game->tileAtlas)), player({ size / 2, size / 2 }, 
		game->textureManager, std::make_shared<Labyrinth>(labyrinth))
{
	this->game = game;
	background.setTexture(game->textureManager.getTexture("labyrinthBackground"));
	sf::Vector2f pos = sf::Vector2f(game->window.getSize());
	guiView.setSize(pos);
	gameView.setSize(pos);
	pos *= 0.5f;
	guiView.setCenter(pos);
	gameView.setCenter(pos);
}
