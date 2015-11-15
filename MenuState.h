#pragma once

#include "State.h"
#include "GameState.h"

class MenuState :
	public State
{
	sf::View view;

	void loadGame();

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	MenuState(std::shared_ptr<GameManager> game);
};

