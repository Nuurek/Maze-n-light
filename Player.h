#pragma once

#include "AnimationHandler.h"
#include "Directions.h"
#include "TextureManager.h"
#include "Labyrinth.h"

enum class PlayerAction
{
	Standing, Walking
};

class Player
{
	float movementTime{ 0.1f };
	float time;
	std::pair<int, int> positionOffset;

public:
	AnimationHandler animationHandler;
	sf::Sprite sprite;

	static const unsigned int frameSize = 48;
	Coordinates position;
	PlayerAction currentAction;
	Directions currentDirection;
	std::shared_ptr<Labyrinth> labyrinth;

	void move(Directions direction);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window, float deltaTime);
	Player(Coordinates startPosition, TextureManager& textureManager, std::shared_ptr<Labyrinth> labyrinth);

	std::pair<int, int> truePosition();
};

