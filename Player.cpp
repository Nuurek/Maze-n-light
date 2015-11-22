#include "Player.h"



void Player::move(Directions direction)
{
	if (currentAction == PlayerAction::Standing)
	{
		if ((direction == Directions::Up && (position.x == 0 || labyrinth->at(position.x - 1, position.y).makeCollision)) ||
			(direction == Directions::Right && (position.y == labyrinth->width - 1 ||labyrinth->at(position.x, position.y + 1).makeCollision)) ||
			(direction == Directions::Down && (position.x == labyrinth->height - 1 || labyrinth->at(position.x + 1, position.y).makeCollision)) ||
			(direction == Directions::Left && (position.y == 0 ||labyrinth->at(position.x, position.y - 1).makeCollision)))
		{
			currentDirection = direction;
			return;
		}

		++stepsCount;
		currentDirection = direction;
		currentAction = PlayerAction::Walking;
		time = 0;
	}
}

void Player::update(float deltaTime)
{
	switch (currentAction)
	{
		case (PlayerAction::Walking) :
		{
			if (time + deltaTime > movementTime)
			{
				currentAction = PlayerAction::Standing;
				switch (currentDirection)
				{
					case (Directions::Up) :
						position.x -= 1;
						break;
					case(Directions::Right) :
						position.y += 1;
						break;
					case(Directions::Down) :
						position.x += 1;
						break;
					case(Directions::Left) :
						position.y -= 1;
						break;
				}
				positionOffset = { 0, 0 };
				time = 0;
				return;
			}
			time += deltaTime;
			int offset = static_cast<int>((time / movementTime) * static_cast<float>(Player::frameSize));
			switch (currentDirection)
			{
				case (Directions::Up) :
					positionOffset.x = -offset;
					break;
				case(Directions::Right) :
					positionOffset.y = offset;
					break;
				case(Directions::Down) :
					positionOffset.x = offset;
					break;
				case(Directions::Left) :
					positionOffset.y = -offset;
					break;
			}

		}
	}
}

void Player::draw(sf::RenderWindow & window, float deltaTime)
{
	switch (currentAction)
	{
		case (PlayerAction::Standing) :
			animationHandler.changeAnimation(2 * static_cast<int>(currentDirection));
			break;
		case(PlayerAction::Walking) :
			animationHandler.changeAnimation(2 * static_cast<int>(currentDirection) + 1);
	}
	sf::Vector2f mapPosition;
	mapPosition.y = static_cast<float>(position.x * Player::frameSize + positionOffset.x);
	mapPosition.x = static_cast<float>(position.y * Player::frameSize + positionOffset.y);
	sprite.setPosition(mapPosition);
	animationHandler.update(deltaTime);
	sprite.setTextureRect(animationHandler.bounds);
	window.draw(sprite);
}

Player::Player(Coordinates startPosition, TextureManager& textureManager, std::shared_ptr<Labyrinth> labyrinth)
{
	position = startPosition;
	stepsCount = 0;
	this->labyrinth = labyrinth;
	positionOffset = sf::Vector2i(0, 0);
	currentAction = PlayerAction::Standing;
	currentDirection = Directions::Down;
	sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite.setTexture(textureManager.getTexture("playerTexture"));
	animationHandler.frameSize = sf::IntRect(0, 0, frameSize, frameSize);
	Animation staticAnimation = Animation(0, 2, 1.0f);
	Animation movementAnimation = Animation(0, 2, movementTime / 3.0f);
	time = 0.0f;
	for (unsigned int i = 0; i < 4; i++)
	{
		animationHandler.addAnim(staticAnimation);
		animationHandler.addAnim(movementAnimation);
	}
	animationHandler.changeAnimation(2 * static_cast<int>(currentDirection));
}

sf::Vector2f Player::truePosition()
{

	return sf::Vector2f((static_cast<float>(position.y) + 0.5f) * static_cast<float>(Player::frameSize) + positionOffset.y, 
		(static_cast<float>(position.x) + 0.5f) * static_cast<float>(Player::frameSize) + positionOffset.x);
}
