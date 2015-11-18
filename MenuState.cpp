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
	
	for (auto gui : guiSystem)
		game->window.draw(gui.second);
}

void MenuState::update(const float dt)
{

}

void MenuState::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePosition = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view);

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				game->window.close();
				break;
			}
			
			case sf::Event::MouseMoved:
			{
				guiSystem.at("menu").highlight(guiSystem.at("menu").getEntry(mousePosition));
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::string message = guiSystem.at("menu").activate(mousePosition);

					if (message == "load_game")
					{
						loadGame();
					}
					else if (message == "exit_game")
					{
						game->window.close();
					}
				}
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
	sf::Vector2f position = static_cast<sf::Vector2f>(game->window.getSize());
	view.setSize(position);
	position *= 0.5f;
	view.setCenter(position);
	float buttonWidth = 192;
	float buttonHeight = 32;

	guiSystem.emplace("menu", Gui(sf::Vector2f(buttonWidth, buttonHeight), 4, false, game->styleSheets.at("text"),
	{
		std::make_pair("Start Game", "load_game"),
		std::make_pair("Exit", "exit_game"),
	}));
	guiSystem.at("menu").setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2 - (static_cast<float>(guiSystem.size()) * 0.5f) * buttonHeight);
	guiSystem.at("menu").setOrigin(buttonWidth / 2, buttonHeight / 2);
	guiSystem.at("menu").show();
}
