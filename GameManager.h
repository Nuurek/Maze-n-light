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
	//Loader functions starting with the start of the game.
	void loadTextures();
	void loadTiles();	
	void loadStyleSheets();
	void loadFonts();

public:
	//Constant values describing save files.
	const std::string saveFilename = "gamesave.dat";
	const std::string scoresFilename = "highscores.dat";
	const unsigned int highScoresNumber = 10;

	//Stack of the States. Top state is the current state.
	std::stack<std::shared_ptr<State>> states;
	
	//Main window of the game, actually the only one.
	sf::RenderWindow window;

	//Management variables. Create types and styles at the beggining, use many times.
	TextureManager textureManager;
	std::map<std::string, Tile> tileAtlas;
	std::map<std::string, GuiStyle> styleSheets;
	std::map<std::string, sf::Font> fonts;

	//Pointer to the current state.
	std::shared_ptr<State> currentState();
	//Aliases of STL stack functions.
	void pushState(std::shared_ptr<State> state);
	void popState();
	void changeState(std::shared_ptr<State> state);

	//Self explanatory, gameloop iterate every time interval through state main functions:
	//handleInput, update, draw.
	void gameLoop();
	//Clear program using destructors and close the game.
	void closeGame();

	GameManager();
	~GameManager();
};

