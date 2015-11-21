#include "MenuState.h"

void MenuState::draw(const float dt)
{
	game->window.setView(view);
	game->window.clear(sf::Color::Black);
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

	sf::Vector2f mousePosition = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window), view);

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				game->closeGame();
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
					guiSystem.at("menu").resetHighlights();

					std::string message = guiSystem.at("menu").activate(mousePosition);

					if (message == "start_game")
					{
						game->pushState(std::make_shared<OptionsState>(game));
					}
					else if (message == "load_game")
					{
						game->pushState(std::make_shared<GameState>(game, game->saveFilename));
					}
					else if (message == "high_scores")
					{
						game->pushState(std::make_shared<HighScoresState>(game, game->scoresFilename));
					}
					else if (message == "exit_game")
					{
						game->closeGame();
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
	guiSystem.emplace("menu", Gui(sf::Vector2f(buttonWidth, buttonHeight), 6, false, game->styleSheets.at("text"),
	{
		std::make_pair("Start Game", "start_game"),
		std::make_pair("Load game", "load_game"),
		std::make_pair("High scores", "high_scores"),
		std::make_pair("Exit", "exit_game")
	}));
	guiSystem.at("menu").setPosition(static_cast<float>(game->window.getSize().x) / 2.0f,
		static_cast<float>(game->window.getSize().y) / 2.0f - ((static_cast<float>(guiSystem.at("menu").entries.size() - 1) * 0.5f) * buttonHeight));
	guiSystem.at("menu").setOrigin(buttonWidth / 2, buttonHeight / 2);
	guiSystem.at("menu").show();
}
