#include "GameManager.h"
#include "State.h"


void GameManager::loadTextures()
{
	//Map texture names to files.
	textureManager.loadTexture("menuBackground", "media/menu_background.png");
	textureManager.loadTexture("labyrinthBackground", "media/labyrinth_background.png");
	textureManager.loadTexture("wallTexture", "media/wall.png");
	textureManager.loadTexture("tileTexture", "media/tile.png");
	textureManager.loadTexture("exitTexture", "media/exit.png");
	textureManager.loadTexture("playerTexture", "media/player.png");
}

void GameManager::loadTiles()
{
	//Create tile patterns.
	Animation staticAnimation(0, 0, 1.0f);
	auto staticAnimationVector = std::vector<Animation>(16, staticAnimation);
	tileAtlas["tunnel"] = Tile(TileType::Tunnel, false, textureManager.getTexture("tileTexture"), staticAnimationVector);
	tileAtlas["wall"] = Tile(TileType::Wall, true, textureManager.getTexture("wallTexture"), staticAnimationVector);
	tileAtlas["exit"] = Tile(TileType::Exit, false, textureManager.getTexture("exitTexture"), staticAnimationVector);
}

void GameManager::loadStyleSheets()
{
	//Create GUIstyle sheets.
	styleSheets["text"] = GuiStyle(std::make_shared<sf::Font>(fonts.at("main_font")), 0,
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff),
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00));
	styleSheets["text2"] = GuiStyle(std::make_shared<sf::Font>(fonts.at("main_font")), 4,
		sf::Color(0x00, 0x00, 0x00, 0x66), sf::Color(0x00, 0x00, 0x00, 0xDD), sf::Color(0x00, 0x00, 0x00, 0x00),
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xAA, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00));
	styleSheets["final_credits"] = GuiStyle(std::make_shared<sf::Font>(fonts.at("main_font")), 0,
		sf::Color(0x15, 0x0d, 0x05, 0x88), sf::Color(0x00, 0x00, 0x00, 0x88), sf::Color(0x00, 0x00, 0x00, 0x88),
		sf::Color(0x00, 0x00, 0x00, 0x88), sf::Color(0xff, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00));
	return;
}

void GameManager::loadFonts()
{
	//Load fonts from file.
	sf::Font font;
	font.loadFromFile("media/font.ttf");
	this->fonts["main_font"] = font;
}

void GameManager::closeGame()
{
	//Pop all states (and run their destructors).
	while (!states.empty())
		popState();
	//Close the window.
	window.close();
	
}

void GameManager::pushState(std::shared_ptr<State> state)
{
	states.push(state);
}

void GameManager::popState()
{
	states.pop();
}

void GameManager::changeState(std::shared_ptr<State> state)
{
	if (!states.empty())
		popState();
	pushState(std::move(state));
}

std::shared_ptr<State> GameManager::currentState()
{
	if (states.empty())
		return nullptr;
	return states.top();
}

void GameManager::gameLoop()
{
	sf::Clock clock;
	sf::Time elapsed;
	float deltaTime;

	while (window.isOpen())
	{
		elapsed = clock.restart();
		deltaTime = elapsed.asSeconds();

		//Pass time that has elapsed to state's functions.
		currentState()->handleInput();
		if (currentState() == nullptr)
			continue; 
		currentState()->update(deltaTime);
		//Refresh screen.
		window.clear(sf::Color::Black);
		currentState()->draw(deltaTime);
		window.display();
	}
}

GameManager::GameManager()
{
	//Load all styles.
	loadTextures();
	loadTiles();
	loadFonts();
	loadStyleSheets();

	window.create(sf::VideoMode(800, 600), "Maze 'n' light", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
}


GameManager::~GameManager()
{
	while (!states.empty())
		popState();
}
