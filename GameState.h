#pragma once

#include "State.h"
#include "Labyrinth.h"
#include "Player.h"

class GameState :
	public State
{
	//Describe what's happening in the game.
	enum class GameAction {Playing, Paused, Final};

	//Different views for game(labyrinth and player) and GUI
	//TODO: Right now they are the same, to be used in a future.
	sf::View gameView;
	sf::View guiView;

	//Components of the game.
	std::string playerName;
	GameAction currentAction;
	Labyrinth labyrinth;
	Player player;

	//Common code for both constructors.
	void loadGameStateConfig();
	//Save game to the file
	void saveGame(std::string filename);
	//Checks whether a new score can be placed in high scores,
	//if it is, it will be placed.
	void addScore(std::pair<std::string, unsigned int> newScore);

public:
	//SEE State.h.
	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	//Pass new player's name, a width and a height of the labyrinth or create game using saved file.
	GameState(std::shared_ptr<GameManager> game, std::string playerName, unsigned int width, unsigned int height);
	GameState(std::shared_ptr<GameManager> game, std::string filename);
	~GameState();
};

