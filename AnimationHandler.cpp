#include "AnimationHandler.h"



void AnimationHandler::addAnim(Animation & animation)
{
	animations.push_back(animation);
}

void AnimationHandler::update(const float deltaTime)
{
	//If current animation is out of handler's range then return.
	if (currentAnimation >= animations.size() || currentAnimation < 0)
		return;

	float duration = animations[currentAnimation].duration;
	//Check if it is time for next frame.
	unsigned int frame = static_cast<unsigned int>((time + deltaTime) / duration);
	if (frame > static_cast<unsigned int>(time / duration))
	{
		frame %= animations[currentAnimation].getLength();

		bounds = frameSize;
		bounds.left = bounds.width * frame;
		bounds.top = bounds.height * currentAnimation;
	}

	time += deltaTime;
	//If time reaches its maximum then nullify it.
	if (time > duration * animations[currentAnimation].getLength())
		time = 0.0f;
}

void AnimationHandler::changeAnimation(unsigned int animationID)
{
	//Change the animation to another. Return if ID is out of range.
	if (currentAnimation == animationID || animationID >= animations.size() || animationID < 0)
		return;

	currentAnimation = animationID;
	bounds = frameSize;
	bounds.top = bounds.height * animationID;
	time = 0.0f;
}

AnimationHandler::AnimationHandler() : 
	time(0.0f), currentAnimation(-1) { }

AnimationHandler::AnimationHandler(const sf::IntRect & newFrameSize) :
	frameSize(newFrameSize), time(0.0f), currentAnimation(-1) { }
