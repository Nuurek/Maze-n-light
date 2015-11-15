#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "MenuState.h"

int main()
{
	auto gameptr = std::make_shared<GameManager>();
	gameptr->pushState(std::make_shared<MenuState>(gameptr));
	gameptr->gameLoop();
	/*
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	*/
	return 0;
}