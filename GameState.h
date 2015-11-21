#pragma once

#include "State.h"
#include "Labyrinth.h"
#include "Player.h"

class GameState :
	public State
{
	enum class GameAction {Playing, Paused, Final};

	sf::View gameView;
	sf::View guiView;

	std::string playerName;

	void loadGameStateConfig();
	void addScore(std::pair<std::string, unsigned int> newScore);

public:
	Labyrinth labyrinth;
	Player player;

	GameAction currentAction;

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();
	void saveGame(std::string filename);

	GameState(std::shared_ptr<GameManager> game, std::string playerName, unsigned int width, unsigned int height);
	GameState(std::shared_ptr<GameManager> game, std::string filename);
	~GameState();
};

