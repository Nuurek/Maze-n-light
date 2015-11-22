#pragma once

#include "AnimationHandler.h"
#include "Directions.h"
#include "TextureManager.h"
#include "Labyrinth.h"

class Player
{
	//Full time of a one movement action.
	float movementTime{ 0.1f };
	//Current time of action.
	float time;
	//The number of pixels the player stands out from its position, based on the 'time' value.
	sf::Vector2i positionOffset;

public:
	//Actions that player can take.
	enum class PlayerAction
	{
		Standing, Walking
	}; 
	
	//Graphic of the player, animationHandler handles the animation(N. Cage meme here).
	//Currently only the movement and standing animation.
	AnimationHandler animationHandler;
	sf::Sprite sprite;
	//Player's frame size in pixels.
	static const unsigned int frameSize = 48;
	//Current position, count of the steps that player has taken from the start,
	//his/her current action and direction.
	Coordinates position;
	unsigned int stepsCount;
	PlayerAction currentAction;
	Directions currentDirection;
	//Pointer to the labyrinth in which a player is currently playing.
	std::shared_ptr<Labyrinth> labyrinth;
	//Returns true positions of player on the window.
	sf::Vector2f truePosition();

	//Moves player into a given direction. Checks before if there is no wall or an edge of the labyrinth.
	void move(Directions direction);
	//Updates animation and state of the player with given time difference.
	void update(float deltaTime);
	//Draws the player on the windows.
	void draw(sf::RenderWindow& window, float deltaTime);

	Player() : currentAction(PlayerAction::Standing), currentDirection(Directions::Down), stepsCount(0) {};
	Player(Coordinates startPosition, TextureManager& textureManager, std::shared_ptr<Labyrinth> labyrinth);
};

