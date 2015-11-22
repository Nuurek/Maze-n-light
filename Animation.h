#pragma once
/*
Animation structure contains number of start frame and end frame
so we can skip some frames on sprite. It also contains duration of a frame.
*/
struct Animation
{
	
	unsigned int startFrame, endFrame;
	
	//Duration is the TIME OF ONLY ONE FRAME, NOT THE WHOLE ANIMATION!
	float duration;

	Animation(unsigned int start, unsigned int end, float dur) : 
		startFrame(start), endFrame(end), duration(dur) { }

	unsigned int getLength() { return endFrame - startFrame + 1; }
};

