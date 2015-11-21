#include "HighScoresState.h"



void HighScoresState::loadHighScores(std::string filename)
{
	std::ifstream file(filename);
	for (unsigned int index = 0; index < game->highScoresNumber; index++)
	{
		file >> highScores[index].first >> highScores[index].second;
	}
}

void HighScoresState::saveHighScores(std::string filename)
{
	std::ofstream file(filename);
	for (auto score : highScores)
	{
		file << score.first << "\t" << score.second << "\n";
	}
}

void HighScoresState::resetHighScores()
{
	highScores = {
		std::make_pair("Caterina" , 100),
		std::make_pair("Reggie" , 90),
		std::make_pair("Xiomara" , 80),
		std::make_pair("Donnell" , 70),
		std::make_pair("Han" , 60),
		std::make_pair("Suzan" , 50),
		std::make_pair("Bettyann" , 40),
		std::make_pair("Julian" , 30),
		std::make_pair("Michiko" , 20),
		std::make_pair("Eleonor" , 10)
	};
	saveHighScores(scoresFilename);
	refreshHighScores();
}

void HighScoresState::refreshHighScores()
{
	unsigned int index = 0;
	for (auto highScore : highScores)
	{
		guiSystem.at("names").entries[index].text.setString(highScore.first);
		guiSystem.at("scores").entries[index++].text.setString(std::to_string(highScore.second));
	}
}

void HighScoresState::draw(const float dt)
{
	game->window.setView(view);
	game->window.clear(sf::Color::Black);
	game->window.draw(background);

	for (auto gui : guiSystem)
		game->window.draw(gui.second);
}

void HighScoresState::update(const float dt)
{
}

void HighScoresState::handleInput()
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

					if (message == "reset_scores")
					{
						resetHighScores();
					}
					else if (message == "main_menu")
					{
						game->popState();
					}
				}
				break;
			}

			default:
			break;
		}
	}
}

HighScoresState::HighScoresState(std::shared_ptr<GameManager> game, std::string highScoresFilename) :
	scoresFilename(highScoresFilename)
{
	this->game = game;
	loadHighScores(scoresFilename);

	background.setTexture(game->textureManager.getTexture("menuBackground"));
	sf::Vector2f position = static_cast<sf::Vector2f>(game->window.getSize());
	view.setSize(position);
	position *= 0.5f;
	view.setCenter(position);

	float buttonWidth = 192;
	float buttonHeight = 32;
	float highScoreHeight = 32;
	float nameWidth = 256; 
	float scoreWidth = 64;

	guiSystem.emplace("buttons", Gui(sf::Vector2f(buttonWidth, buttonHeight), 4, false, game->styleSheets.at("text2"),
	{
		std::make_pair("Back", "main_menu"),
		std::make_pair("Reset scores", "reset_scores")
	}));
	guiSystem.at("buttons").setPosition(game->window.getSize().x - buttonWidth / 2, buttonHeight / 2);
	guiSystem.at("buttons").setOrigin(buttonWidth / 2, buttonHeight /2);
	guiSystem.at("buttons").show();

	std::vector < std::pair<std::string, std::string>> namesVector;
	std::vector < std::pair<std::string, std::string>> scoresVector;
	for (auto highScore : highScores)
	{
		namesVector.emplace_back(std::make_pair(highScore.first, "null"));
		scoresVector.emplace_back(std::make_pair(std::to_string(highScore.second), "null"));
	}
	guiSystem.emplace("names", Gui(sf::Vector2f(nameWidth, highScoreHeight), 4, false, game->styleSheets.at("text2"), namesVector));
	guiSystem.emplace("scores", Gui(sf::Vector2f(scoreWidth, highScoreHeight), 4, false, game->styleSheets.at("text2"), scoresVector));
	
	guiSystem.at("names").setPosition(game->window.getSize().x / 2 - scoreWidth / 2, 9 * highScoreHeight / 2);
	guiSystem.at("names").setOrigin(nameWidth / 2, highScoreHeight / 2);
	guiSystem.at("names").show();

	guiSystem.at("scores").setPosition(game->window.getSize().x / 2 + nameWidth / 2, 9 * highScoreHeight / 2);
	guiSystem.at("scores").setOrigin(scoreWidth / 2, highScoreHeight / 2);
	guiSystem.at("scores").show();
}

HighScoresState::~HighScoresState()
{
	saveHighScores(scoresFilename);
}

