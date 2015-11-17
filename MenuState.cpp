#include "MenuState.h"

void MenuState::loadGame()
{
	game->pushState(std::make_shared<GameState>(game, 23));
}

void MenuState::draw(const float dt)
{
	game->window.setView(view);
	game->window.clear(sf::Color::Blue);
	game->window.draw(background);
}

void MenuState::update(const float dt)
{

}

void MenuState::handleInput()
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
					game->window.close();
				else if (event.key.code == sf::Keyboard::Space)
					loadGame();
				break;
			}

			default:
			break;
		}
	}
}

MenuState::MenuState(std::shared_ptr<GameManager> game)
{
	this->game = game;
	background.setTexture(game->textureManager.getTexture("menuBackground"));
	sf::Vector2f pos = static_cast<sf::Vector2f>(game->window.getSize());
	view.setSize(pos);
	pos *= 0.5f;
	view.setCenter(pos);
}
