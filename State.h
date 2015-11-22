#pragma once
#include <memory>
#include <fstream>
#include "GameManager.h"
#include "TextureManager.h"
#include "Gui.h"

class GameManager;

//Base class for all states in a game.
class State
{
protected:
	//Variable maps names of the GUI systems into GUIs.
	//Easier to use.
	std::map<std::string, Gui> guiSystem;
	//Background of the state.
	sf::Sprite background;
	//Pointer to the game from which state has been started.
	std::shared_ptr<GameManager> game;

public:
	//Draw state.
	virtual void draw(const float deltaTime) = 0;
	//Update state depending on given time difference and take appropriate actions.
	virtual void update(const float deltaTime) = 0;
	//Handle input other than clock: mouse and keyboard mainly.
	virtual void handleInput() = 0;
};

