#pragma once
#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "State.h"
#include "TextureManager.h"
#include "AnimationHandler.h"
#include "Tile.h"
#include "Gui.h"

class State;

class GameManager
{
	void loadTextures();
	void loadTiles();
	void loadStyleSheets();
	void loadFonts();

public:
	const std::string saveFilename = "gamesave.dat";
	const std::string scoresFilename = "highscores.dat";
	const int highScoresNumber = 10;


	std::stack<std::shared_ptr<State>> states;
	
	sf::RenderWindow window;
	TextureManager textureManager;
	std::map<std::string, Tile> tileAtlas;
	std::map<std::string, GuiStyle> styleSheets;
	std::map<std::string, sf::Font> fonts;

	void pushState(std::shared_ptr<State> state);
	void popState();
	void changeState(std::shared_ptr<State> state);
	std::shared_ptr<State> currentState();

	void gameLoop();
	void closeGame();

	GameManager();
	~GameManager();
};

