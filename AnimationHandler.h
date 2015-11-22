#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

#include "Animation.h"

class AnimationHandler
{
	//Vector of animations.
	std::vector<Animation> animations;
	//Current time of animation.
	float time;
	//Index of current animation.
	unsigned int currentAnimation;

public:
	//Add new animation to handler.
	void addAnim(Animation& animation);
	//Advance with frames of current animation if interval has passed.
	void update(const float deltaTime);
	//Change animation to another based on their ID.
	void changeAnimation(unsigned int animationID);

	//Current 'view' into animation sprite.
	sf::IntRect bounds;
	//Size of the frame of the animation, almost always constant.
	sf::IntRect frameSize;

	AnimationHandler();
	//Construct handler based on its frame's size.
	AnimationHandler(const sf::IntRect& frameSize);
};

