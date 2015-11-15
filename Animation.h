#pragma once
struct Animation
{
	unsigned int startFrame, endFrame;

	float duration;

	Animation(unsigned int start, unsigned int end, float dur) : 
		startFrame(start), endFrame(end), duration(dur) { }

	unsigned int getLength() { return endFrame - startFrame + 1; }
};

