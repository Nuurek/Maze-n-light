#include "GameState.h"

void GameState::loadGameStateConfig()
{
	currentAction = GameAction::Playing;

	background.setTexture(game->textureManager.getTexture("labyrinthBackground"));
	sf::Vector2f position = sf::Vector2f(game->window.getSize());
	guiView.setSize(position);
	gameView.setSize(position);
	position *= 0.5f;
	guiView.setCenter(position);
	gameView.setCenter(position);

	float buttonWidth = 192;
	float buttonHeight = 32;
	guiSystem.emplace("menu", Gui(sf::Vector2f(buttonWidth, buttonHeight), 4, false, game->styleSheets.at("text2"),
	{
		std::make_pair("Main menu", "exit_to_menu"),
		std::make_pair("Exit", "exit_game"),
	}));
	guiSystem.at("menu").setPosition(game->window.getSize().x - buttonWidth / 2, buttonHeight / 2);
	guiSystem.at("menu").setOrigin(buttonWidth / 2, buttonHeight / 2);
	guiSystem.at("menu").hide();

	float finalWidth = 1000;
	float finalHeight = 48;
	guiSystem.emplace("final", Gui(sf::Vector2f(finalWidth, finalHeight), 0, false, game->styleSheets.at("final_credits"),
	{
		std::make_pair("The least number of steps was: ", "null"),
		std::make_pair("You did it with ", "null"),
		std::make_pair(" steps, congratulations.", "null"),
		std::make_pair("Your score: ", "null")
	}));
	guiSystem.at("final").setOrigin(finalWidth / 2, finalHeight / 2);
	guiSystem.at("final").hide();
}

void GameState::addScore(std::pair<std::string, unsigned int> newScore)
{
	std::fstream file(game->scoresFilename);
	std::array<std::pair<std::string, unsigned int>, 10> highScores;
	for (unsigned int index = 0; index < game->highScoresNumber; index++)
		file >> highScores[index].first >> highScores[index].second;
	file.close();

	unsigned int index = game->highScoresNumber - 1;
	while (index > 0 && newScore.second > highScores[index].second)
	{
		highScores[index] = highScores[index - 1];
		--index;
	}
	highScores[index] = newScore;

	file.open(game->scoresFilename);
	for (auto score : highScores)
		file << score.first << "\t" << score.second << "\n";
	file.close();
}

void GameState::draw(const float deltaTime)
{
	auto truePosition = player.truePosition();
	gameView.setCenter(truePosition);
	guiView.setCenter(truePosition);
	game->window.setView(gameView);
	game->window.clear(sf::Color::Black);
	labyrinth.draw(game->window, deltaTime);
	player.draw(game->window, deltaTime);

	game->window.setView(guiView);
	guiSystem.at("menu").setPosition(truePosition.x - game->window.getSize().x / 2 + guiSystem.at("menu").getOrigin().x, 
		truePosition.y - game->window.getSize().y / 2 + guiSystem.at("menu").getOrigin().y);
	guiSystem.at("final").setPosition(truePosition.x, truePosition.y - 3.0f * guiSystem.at("final").getOrigin().y);
	for (auto& gui : guiSystem)
	{
		game->window.draw(gui.second);
	}
}

void GameState::update(const float deltaTime)
{
	switch(currentAction)
	{
		case(GameAction::Playing):
			if (player.position == labyrinth.exit)
			{
				currentAction = GameAction::Final;
				std::string text;
				text = guiSystem.at("final").entries[0].text.getString();
				text += std::to_string(labyrinth.shortestPathLength);
				guiSystem.at("final").entries[0].text.setString(text);

				text = guiSystem.at("final").entries[2].text.getString();
				text.insert(0, std::to_string(player.stepsCount));
				guiSystem.at("final").entries[2].text.setString(text);

				text = guiSystem.at("final").entries[3].text.getString();
				unsigned int score = static_cast<unsigned int>(static_cast<float>(labyrinth.shortestPathLength / static_cast<float>(player.stepsCount))
					* static_cast<float>(labyrinth.width * labyrinth.height));
				text += std::to_string(score);
				guiSystem.at("final").entries[3].text.setString(text);

				guiSystem.at("menu").show();
				guiSystem.at("final").show();

				addScore(std::make_pair(playerName, score));
			}
			player.update(deltaTime);
			break;
		case(GameAction::Paused) :
			break;
		case(GameAction::Final) :
			break;
	}
}

void GameState::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePosition = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window), this->gameView);

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
					std::string message = guiSystem.at("menu").activate(mousePosition);

					if (message == "exit_to_menu")
					{
						game->popState();
					}
					else if (message == "exit_game")
					{
						game->closeGame();
					}
				}
				guiSystem.at("menu").highlight(-1);
				break;
			}

			case sf::Event::KeyPressed:
			{
				if (currentAction == GameAction::Playing)
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
							currentAction = GameAction::Paused;
							guiSystem.at("menu").show();
							break;
					}
				}
				else if(currentAction == GameAction::Paused)
				{
					switch (event.key.code)
					{
						case (sf::Keyboard::Escape) :
						{
							guiSystem.at("menu").hide();
							currentAction = GameAction::Playing;
							break;
						}
					}
				}
			}
			default: 
			break;
		}
	}
}

void GameState::saveGame(std::string filename)
{
	std::ofstream file(filename, std::ios::out);
	file << playerName << "\t" << player.position.x << "\t" << player.position.y << "\t" << player.stepsCount << "\n";
	file << labyrinth.width << "\t" << labyrinth.height << "\n";
	for (unsigned int row = 0; row < labyrinth.height; row++)
	{
		for (unsigned int column = 0; column < labyrinth.width; column++)
		{
			file << static_cast<unsigned int>(labyrinth.at(row, column).tileType) << " " << labyrinth.at(row, column).orientation << " ";
		}
		file << "\n";
	}
}

GameState::GameState(std::shared_ptr<GameManager> game, std::string playerName, unsigned int width, unsigned int height)
	: labyrinth(Labyrinth(width, height, game->textureManager, game->tileAtlas)), player({ height / 2, width/ 2 }, 
		game->textureManager, std::make_shared<Labyrinth>(labyrinth))
{
	this->game = game;
	this->playerName = playerName;
	loadGameStateConfig();
}

GameState::GameState(std::shared_ptr<GameManager> game, std::string filename)
	: labyrinth(filename, game->textureManager, game->tileAtlas)
{
	this->game = game;
	std::ifstream file(filename, std::ios::in);
	unsigned int playerX, playerY, stepsCount;
	file >> playerName >> playerX >> playerY >> stepsCount;

	player = Player({ playerX, playerY }, game->textureManager, std::make_shared<Labyrinth>(labyrinth));
	player.stepsCount = stepsCount;

	loadGameStateConfig();
}

GameState::~GameState()
{
	if (currentAction != GameAction::Final)
		saveGame(game->saveFilename);
}
