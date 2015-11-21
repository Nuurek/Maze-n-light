#pragma once
#include "State.h"
#include "GameState.h"

class OptionsState :
	public State
{
	sf::View view;

	bool input;
	std::string inputText;

	std::pair<std::string, bool> playerName;
	std::pair<std::string, bool> labyrinthWidth;
	std::pair<std::string, bool> labyrinthHeight;

public:
	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	OptionsState(std::shared_ptr<GameManager> game);
};

