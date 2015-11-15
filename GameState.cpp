#include "GameState.h"

void GameState::draw(const float deltaTime)
{
	game->window.clear();
	game->window.draw(background);
	labyrinth.draw(game->window, deltaTime);
}

void GameState::update(const float dt)
{

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
				if (event.key.code == sf::Keyboard::Escape)
					game->popState();
				else if (event.key.code == sf::Keyboard::S)
					labyrinth.solveMaze();
			}
			default: 
			break;
		}
	}
}

GameState::GameState(std::shared_ptr<GameManager> game)
	: labyrinth(Labyrinth(11, 11, game->textureManager, game->tileAtlas))
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
