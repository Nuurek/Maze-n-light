#pragma once
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include "SFML\Graphics.hpp"

//Describes how will the GUI look like.
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

//Combines a shape of the entry and a displayed text with internal message that will be send by
//GUI when a mouse hovers over.
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

//Derives from SFML classes: Drawable and Transformable, which allows
//to draw it using window's handler and transformate it as every other SFML object.
class Gui : 
	public sf::Drawable, public sf::Transformable
{
	//Is GUI horizontal or vertical.
	bool horizontal;
	//Linked GUIStyle.
	GuiStyle style;
	//Size of the GUI.
	sf::Vector2f dimensions;
	//Surrounds the text to stop it from overlapping the edges.
	//Negative means edges going beyong the shape.
	int padding;

public:
	//Vector of GUI entries.
	std::vector<GuiEntry> entries;
	//Is GUI visible?
	bool visible;
	//Gettter for GUI size.
	sf::Vector2f getSize();
	//Returns message from GUI if mouse hover over entries.
	int getEntry(const sf::Vector2f mousePosition);
	//Sets new visible text for one of the entries.
	void setEntryText(unsigned int entry, std::string text);
	//Sets new size.
	void setDimensions(sf::Vector2f dimensions);
	//Virtual function, draws GUI into windows.
	//TODO: RenderStates:: blend mode, shaders, transformations.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//Changes visibility of the GUI to true.
	void show();
	//Changes visibility of the GUI to false.
	void hide();
	//Highlights entry.
	void highlight(const int entry);
	//Turns off highlights of the all entries.
	void resetHighlights();
	//Returns message related to entry, based on index or mouse position.
	std::string activate(const int entry);
	std::string activate(const sf::Vector2f mousePosition);

	Gui(sf::Vector2f dimensions, int padding, bool horizontal,
		GuiStyle& style, std::vector<std::pair<std::string, std::string>> entries);
};

