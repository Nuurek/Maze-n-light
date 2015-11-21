#pragma once
#include <string>
#include <array>
#include <utility>
#include <fstream>

#include "State.h"
class HighScoresState :
	public State
{
	sf::View view;

	std::array<std::pair<std::string, unsigned int>, 10> highScores;
	const std::string scoresFilename;

	void loadHighScores(std::string filename);
	void saveHighScores(std::string filename);
	void resetHighScores();
	void refreshHighScores();

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	HighScoresState(std::shared_ptr<GameManager> game, std::string highScoresFilename);
	~HighScoresState();
};

