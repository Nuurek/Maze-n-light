#pragma once

#include "State.h"
#include "GameState.h"

class MenuState :
	public State
{
	sf::View view;

	std::map<std::string, Gui> guiSystem;

	void loadGame();

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	MenuState(std::shared_ptr<GameManager> game);
};

