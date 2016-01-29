#include "stdio.h"

#include "SFML/Graphics.hpp"

#include "game.h"

int main(int argc, char* argv[])
{
	MorningRitual::Game game;
	
	game.run();
	
	return 0;
	
	/*
	sf::RenderWindow window(sf::VideoMode(800, 600), "GGJ-2016");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	int time = 0;
	sf::Color colours[5] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::White};
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		
		window.clear(colours[time % 5]);
		
		//Draw things here
		
		window.display();
		
		time ++;
	}

	return 0;
	*/
}
