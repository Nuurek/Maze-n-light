#pragma once

#include "AnimationHandler.h"
#include "Directions.h"
#include "TextureManager.h"
#include "Labyrinth.h"

class Player
{
	float movementTime{ 0.1f };
	float time;
	sf::Vector2i positionOffset;

public:
	AnimationHandler animationHandler;
	sf::Sprite sprite;


	enum class PlayerAction
	{
		Standing, Walking
	};

	static const unsigned int frameSize = 48;
	Coordinates position;
	unsigned int stepsCount;
	PlayerAction currentAction;
	Directions currentDirection;
	std::shared_ptr<Labyrinth> labyrinth;

	void move(Directions direction);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window, float deltaTime);
	Player() : currentAction(PlayerAction::Standing), currentDirection(Directions::Down), stepsCount(0) {};
	Player(Coordinates startPosition, TextureManager& textureManager, std::shared_ptr<Labyrinth> labyrinth);

	sf::Vector2f truePosition();
};

