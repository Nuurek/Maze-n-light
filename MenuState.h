#pragma once

#include "State.h"
#include "GameState.h"
#include "HighScoresState.h"
#include "OptionsState.h"

class MenuState :
	public State
{
	const std::string& saveFilename = game->saveFilename;
	const std::string& scoresFilename = game->scoresFilename;

	sf::View view;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	MenuState(std::shared_ptr<GameManager> game);
};

