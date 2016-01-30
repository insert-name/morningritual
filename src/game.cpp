#include "stdio.h"

#include "game.h"

namespace MorningRitual
{
	Game::Game()
	{
		printf("Created game\n");
		
		this->window.create(sf::VideoMode(800, 600), "Morning Ritual");
		
		printf("Created window of size %dx%d\n", this->window.getSize().x, this->window.getSize().y);
		
		this->view.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
		this->view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		
		this->window.setView(this->view);
		
		printf("Created view\n");
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
