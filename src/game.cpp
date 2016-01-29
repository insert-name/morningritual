#include "stdio.h"

#include "game.h"

namespace MorningRitual
{
	Game::Game()
	{
		printf("Created game\n");
		
		this->window.create(sf::VideoMode(800, 600), "Morning Ritual");
	}
	
	void Game::run()
	{
		printf("Running game...\n");
		
		while (this->window.isOpen())
		{
			sf::Event event;
			while (this->window.pollEvent(event))
			{
				switch(event.type)
				{
					case sf::Event::Closed:
						this->window.close();
						break;
					default:
						break;
				}
			}
			
			this->draw();
		}
	}
	
	void Game::draw()
	{
		this->window.clear(sf::Color::Blue);
		
		
		
		this->window.display();
	}
}
