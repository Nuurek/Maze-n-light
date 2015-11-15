#pragma once
#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "State.h"
#include "TextureManager.h"
#include "AnimationHandler.h"
#include "Tile.h"

class State;

class GameManager
{
	void loadTextures();
	void loadTiles();

public:
	std::stack<std::shared_ptr<State>> states;
	
	sf::RenderWindow window;
	TextureManager textureManager;
	std::map<std::string, Tile> tileAtlas;

	void pushState(std::shared_ptr<State> state);
	void popState();
	void changeState(std::shared_ptr<State> state);
	std::shared_ptr<State> currentState();

	void gameLoop();

	GameManager();
	~GameManager();
};

