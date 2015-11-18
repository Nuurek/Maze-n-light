#pragma once
#include <iostream>
#include "Directions.h"
#include <vector>

template <class NodeType> class MazePrimitive
{
protected:
	std::vector<NodeType> maze;

	unsigned int index(unsigned int row, unsigned int column)
	{
		return row * width + column;
	}
	std::pair<unsigned int, unsigned int>indexToCoordinates(unsigned int index)
	{
		return std::pair<unsigned int, unsigned int>(index / width, index % width);
	}
public:
	unsigned int width, height;

	NodeType at(unsigned int x, unsigned int y)
	{
		return maze[index(x, y)];
	}

	MazePrimitive(unsigned int newWidth, unsigned int newHeight)
		: width(newWidth), height(newHeight) { }
};