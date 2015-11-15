#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

#include "Animation.h"

class AnimationHandler
{
	std::vector<Animation> animations;

	float time;

	unsigned int currentAnimation;

public:
	void addAnim(Animation& animation);
	void update(const float deltaTime);
	void changeAnimation(unsigned int animationID);

	sf::IntRect bounds;
	sf::IntRect frameSize;

	AnimationHandler();
	AnimationHandler(const sf::IntRect& frameSize);
};

