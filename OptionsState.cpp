#include "OptionsState.h"



void OptionsState::draw(const float deltaTime)
{
	game->window.setView(view);
	game->window.clear(sf::Color::Black);
	game->window.draw(background);

	guiSystem.at("inputEntries").resetHighlights();
	if(playerName.second)
		guiSystem.at("inputEntries").highlight(0);
	if (labyrinthWidth.second)
		guiSystem.at("inputEntries").highlight(1);
	if (labyrinthHeight.second)
		guiSystem.at("inputEntries").highlight(2);

	for (auto gui : guiSystem)
		game->window.draw(gui.second);
}

void OptionsState::update(const float deltaTime)
{
	guiSystem.at("inputEntries").entries[0].text.setString(playerName.first);
	guiSystem.at("inputEntries").entries[1].text.setString(labyrinthWidth.first);
	guiSystem.at("inputEntries").entries[2].text.setString(labyrinthHeight.first);
}

void OptionsState::handleInput()
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
				guiSystem.at("buttons").highlight(guiSystem.at("buttons").getEntry(mousePosition));
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::string message = guiSystem.at("buttons").activate(mousePosition);

					if (message == "exit_to_menu")
					{
						game->popState();
					}
					else if (message == "start_game")
					{
						game->popState();
						game->pushState(std::make_shared<GameState>(game, playerName.first, 
							4 * (std::stoi(labyrinthWidth.first) + 3) - 1,
							4 * (std::stoi(labyrinthHeight.first) + 3) - 1));
					}
					
					message = guiSystem.at("inputEntries").activate(mousePosition);

					if (message == "player_name_input" || message == "labyrinth_width_input" || message == "labyrinth_height_input")
					{
						input = true;
						if (message == "player_name_input")
						{
							playerName.first.clear();
							playerName.second = true;
							labyrinthWidth.second = false;
							labyrinthHeight.second = false;
						}
						else if (message == "labyrinth_width_input")
						{
							playerName.second = false;
							labyrinthWidth.second = true;
							labyrinthHeight.second = false;
						}
						else if (message == "labyrinth_height_input")
						{
							playerName.second = false;
							labyrinthWidth.second = false;
							labyrinthHeight.second = true;
						}
					}
					else
					{
						input = false;
						playerName.second = false;
						labyrinthWidth.second = false;
						labyrinthHeight.second = false;
					}
				}
				break;
			}
			case sf::Event::TextEntered :
			{
				if (event.text.unicode == '\b')
				{
					if (playerName.second && playerName.first.size() > 0)
						playerName.first.erase(playerName.first.size() - 1, 1);
					else if (labyrinthWidth.second && labyrinthWidth.first.size() > 0)
						labyrinthWidth.first.erase(labyrinthWidth.first.size() - 1, 1);
					else if (labyrinthHeight.second && labyrinthHeight.first.size() > 0)
						labyrinthHeight.first.erase(labyrinthHeight.first.size() - 1, 1);
				}
				else if (event.text.unicode < 128)
				{
					if (playerName.second && playerName.first.size() < 16)
						playerName.first += static_cast<char>(event.text.unicode);
					else if (labyrinthWidth.second && event.text.unicode >= 48 && event.text.unicode <= 57)
						labyrinthWidth.first = static_cast<char>(event.text.unicode);
					else if (labyrinthHeight.second && event.text.unicode >= 48 && event.text.unicode <= 57)
						labyrinthHeight.first = static_cast<char>(event.text.unicode);
				}
			}
			case sf::Event::KeyPressed :
			{
				if (event.key.code == sf::Keyboard::Return && input)
				{
					if (playerName.second)
					{
						playerName.second = false;
						labyrinthWidth.second = true;
					}
					else if (labyrinthWidth.second)
					{
						labyrinthWidth.second = false;
						labyrinthHeight.second = true;
					}
					else if (labyrinthHeight.second)
					{
						labyrinthHeight.second = false;
						input = false;
					}
				}
			}

			default:
			break;
		}
	}
}

OptionsState::OptionsState(std::shared_ptr<GameManager> game)
{
	this->game = game;

	input = true;
	playerName = std::make_pair("Player", false);
	labyrinthWidth = std::make_pair("5", false);
	labyrinthHeight = std::make_pair("5", false);

	background.setTexture(game->textureManager.getTexture("menuBackground"));
	sf::Vector2f position = static_cast<sf::Vector2f>(game->window.getSize());
	view.setSize(position);
	position *= 0.5f;
	view.setCenter(position);

	float inputWidth = 256;
	float inputHeight = 32;

	guiSystem.emplace("inputLabels", Gui(sf::Vector2f(inputWidth, inputHeight), 4, false, game->styleSheets.at("text"),
	{
		std::make_pair("Player name:", "null"),
		std::make_pair("Labyrinth width(0-9): ", "null"),
		std::make_pair("Labyrinth height(0-9):", "null"),
	}));
	guiSystem.at("inputLabels").setPosition(static_cast<float>(game->window.getSize().x) / 2.0f - inputWidth / 2,
		static_cast<float>(game->window.getSize().y) / 2.0f - (static_cast<float>(guiSystem.at("inputLabels").entries.size() + 2) * 0.5f) * inputHeight);
	guiSystem.at("inputLabels").setOrigin(inputWidth / 2, inputHeight / 2);
	guiSystem.at("inputLabels").show();

	guiSystem.emplace("inputEntries", Gui(sf::Vector2f(inputWidth, inputHeight), 4, false, game->styleSheets.at("text"),
	{
		std::make_pair("Player", "player_name_input"),
		std::make_pair("5", "labyrinth_width_input"),
		std::make_pair("5", "labyrinth_height_input"),
	}));
	guiSystem.at("inputEntries").setPosition(static_cast<float>(game->window.getSize().x) / 2.0f + inputWidth / 2,
		static_cast<float>(game->window.getSize().y) / 2.0f - (static_cast<float>(guiSystem.at("inputEntries").entries.size() + 2) * 0.5f) * inputHeight);
	guiSystem.at("inputEntries").setOrigin(inputWidth / 2, inputHeight / 2);
	guiSystem.at("inputEntries").show();

	guiSystem.emplace("buttons", Gui(sf::Vector2f(inputWidth, inputHeight), 4, false, game->styleSheets.at("text2"),
	{
		std::make_pair("Start", "start_game"),
		std::make_pair("Back", "exit_to_menu")
	}));
	guiSystem.at("buttons").setPosition(static_cast<float>(game->window.getSize().x) / 2.0f,
		static_cast<float>(game->window.getSize().y) / 1.5f - (static_cast<float>(guiSystem.at("buttons").entries.size() - 1) * 0.5f) * inputHeight);
	guiSystem.at("buttons").setOrigin(inputWidth / 2, inputHeight / 2);
	guiSystem.at("buttons").show();
}
