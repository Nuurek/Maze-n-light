#pragma once
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include "SFML\Graphics.hpp"

class GuiStyle
{
public:
	sf::Color bodyColor;
	sf::Color bodyHighlightColor;
	sf::Color borderColor;
	sf::Color borderHighlightColor;
	sf::Color textColor;
	sf::Color textHighlightColor;
	std::unique_ptr<sf::Font> font;

	float borderSize;

	GuiStyle(std::unique_ptr<sf::Font> font, float borderSize, sf::Color bodyColor, sf::Color bodyHighlightColor,
		sf::Color borderColor, sf::Color borderHighlightColor, sf::Color textColor, sf::Color textHighlightColor) :
		font(std::move(font)), borderSize(borderSize), bodyColor(bodyColor), bodyHighlightColor(bodyHighlightColor),
		borderColor(borderColor), borderHighlightColor(borderHighlightColor), textColor(textColor), textHighlightColor(textHighlightColor)
	{ }

	GuiStyle() {}
};

class Gui
{
public:
	Gui();
	~Gui();
};

