#pragma once

#include "State.h"
#include "Labyrinth.h"

class GameState :
	public State
{
	sf::View gameView;
	sf::View guiView;

public:
	Labyrinth labyrinth;

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	GameState(std::shared_ptr<GameManager> game);
};

