#pragma once
#include <iostream>
#include "Directions.h"
#include <vector>

//Base class for all maze classes.
//Contains 2D array of nodes stored in 1D vector.
//Protected functions allow to convert 1D index into 2D coordinates
//and the other way around.
//Public functions return a node at given coordinates.
template <class NodeType> class MazePrimitive
{
protected:
	std::vector<NodeType> maze;

	unsigned int index(unsigned int row, unsigned int column)
	{
		return row * width + column;
	}
	Coordinates indexToCoordinates(unsigned int index)
	{
		return Coordinates(index / width, index % width);
	}
public:
	unsigned int width, height;

	NodeType at(unsigned int x, unsigned int y)
	{
		return maze[index(x, y)];
	}

	MazePrimitive() : width(0), height(0) {};
	MazePrimitive(unsigned int newWidth, unsigned int newHeight)
		: width(newWidth), height(newHeight) { }
};