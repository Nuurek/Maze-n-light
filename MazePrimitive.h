#pragma once
#include <iostream>
#include "Directions.h"
#include <vector>

template <class NodeType> class MazePrimitive
{
protected:
	using Coordinates = std::pair<unsigned int, unsigned int>;

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

	std::vector<NodeType> maze;

	MazePrimitive(unsigned int newWidth, unsigned int newHeight)
		: width(newWidth), height(newHeight) { }
};