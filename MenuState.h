#pragma once

#include "State.h"
#include "GameState.h"
#include "HighScoresState.h"
#include "OptionsState.h"

//Menu state contains GUI system derived from State class.
class MenuState :
	public State
{
	sf::View view;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	MenuState(std::shared_ptr<GameManager> game);
};

