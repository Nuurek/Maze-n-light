#pragma once
#include <memory>
#include "GameManager.h"
#include "TextureManager.h"

class GameManager;

class State
{
public:
	std::shared_ptr<GameManager> game;
	sf::Sprite background;

	virtual void draw(const float deltaTime) = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void handleInput() = 0;
};

