#pragma once
#include "State.h"
#include "GameState.h"

class OptionsState :
	public State
{
	sf::View view;

	//Is input on?
	bool input;
	
	//Pairs of the input values.
	//Boolean value will be true if this variable is currently changing.
	//TODO: Integrate input with GUI to bypass this kind of ugly syntax :(
	std::pair<std::string, bool> playerName;
	std::pair<std::string, bool> labyrinthWidth;
	std::pair<std::string, bool> labyrinthHeight;

public:
	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	OptionsState(std::shared_ptr<GameManager> game);
};

