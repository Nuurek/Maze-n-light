#pragma once
#include <memory>
#include <fstream>
#include "GameManager.h"
#include "TextureManager.h"
#include "Gui.h"

class GameManager;

class State
{
protected:
	std::map<std::string, Gui> guiSystem;

public:
	std::shared_ptr<GameManager> game;
	sf::Sprite background;

	virtual void draw(const float deltaTime) = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void handleInput() = 0;
};

