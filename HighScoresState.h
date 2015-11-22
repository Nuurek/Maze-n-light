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
	//Current high scores in the game.
	std::array<std::pair<std::string, unsigned int>, 10> highScores;
	//Constant variable describes filename of a file with saved scores.
	const std::string scoresFilename;

	//Loads and saves high scores from file.
	void loadHighScores(std::string filename);
	void saveHighScores(std::string filename);
	//Resets high scores to the base values.
	void resetHighScores();
	//Refreshes GUI without opening file.
	void refreshHighScores();

public:
	//SEE State.h.
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	//Construct only using the file with high scores.
	HighScoresState(std::shared_ptr<GameManager> game, std::string highScoresFilename);
	~HighScoresState();
};

