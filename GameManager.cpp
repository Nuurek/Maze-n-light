#include "GameManager.h"
#include "State.h"


void GameManager::loadTextures()
{
	textureManager.loadTexture("menuBackground", "media/menu_background.png");
	textureManager.loadTexture("labyrinthBackground", "media/labyrinth_background.png");
	textureManager.loadTexture("wallTexture", "media/wall.png");
	textureManager.loadTexture("tileTexture", "media/tile.png");
	textureManager.loadTexture("exitTexture", "media/exit.png");
	textureManager.loadTexture("playerTexture", "media/player.png");
}

void GameManager::loadTiles()
{
	Animation staticAnimation(0, 0, 1.0f);
	auto staticAnimationVector = std::vector<Animation>(16, staticAnimation);
	tileAtlas["corridor"] = Tile(false, textureManager.getTexture("tileTexture"), staticAnimationVector);
	tileAtlas["wall"] = Tile(true, textureManager.getTexture("wallTexture"), staticAnimationVector);
	tileAtlas["exit"] = Tile(false, textureManager.getTexture("exitTexture"), staticAnimationVector);
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

		if (currentState() == nullptr)
			continue;
		currentState()->handleInput();
		currentState()->update(deltaTime);
		window.clear(sf::Color::Black);
		currentState()->draw(deltaTime);
		window.display();
	}
}

GameManager::GameManager()
{
	loadTextures();
	loadTiles();

	window.create(sf::VideoMode(800, 600), "Maze 'n' light", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
}


GameManager::~GameManager()
{
	while (!states.empty())
		popState();
}
