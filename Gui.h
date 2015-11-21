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
	std::shared_ptr<sf::Font> font;

	float borderSize;

	GuiStyle(std::shared_ptr<sf::Font> font, float borderSize, sf::Color bodyColor, sf::Color bodyHighlightColor,
		sf::Color borderColor, sf::Color borderHighlightColor, sf::Color textColor, sf::Color textHighlightColor) :
		font(std::move(font)), borderSize(borderSize), bodyColor(bodyColor), bodyHighlightColor(bodyHighlightColor),
		borderColor(borderColor), borderHighlightColor(borderHighlightColor), textColor(textColor), textHighlightColor(textHighlightColor)
	{ }

	GuiStyle() {}
};

class GuiEntry
{
public:

	sf::RectangleShape shape;

	std::string message;

	sf::Text text;

	GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text) :
		message(message), shape(shape), text(text) { }

	GuiEntry() { }
};

class Gui : 
	public sf::Drawable, public sf::Transformable
{
	bool horizontal;

	GuiStyle style;

	sf::Vector2f dimensions;

	int padding;

public:
	std::vector<GuiEntry> entries;

	bool visible;

	sf::Vector2f getSize();

	int getEntry(const sf::Vector2f mousePosition);

	void setEntryText(int entry, std::string text);

	void setDimensions(sf::Vector2f dimensions);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void show();

	void hide();

	void highlight(const int entry);

	void resetHighlights();

	std::string activate(const int entry);
	std::string activate(const sf::Vector2f mousePosition);

	Gui(sf::Vector2f dimensions, int padding, bool horizontal,
		GuiStyle& style, std::vector<std::pair<std::string, std::string>> entries);
};

