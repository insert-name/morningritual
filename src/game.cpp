#include "stdio.h"

#include "game.h"
#include "common.h"

namespace MorningRitual
{
	Game::Game()
	{
		printf("Created game\n");
		
		this->window.create(sf::VideoMode(800, 600), "Morning Ritual");
		this->window.setVerticalSyncEnabled(true);
		this->window.setFramerateLimit(60);
		
		printf("Created window of size %dx%d\n", this->window.getSize().x, this->window.getSize().y);
		
		this->view.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
		this->view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		
		printf("Created view\n");
		
		this->tileset.loadFromFile("../data/tiles/tileTest.png");
		
		printf("Opened tileset\n");
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
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				this->view_velocity.x -= 2.0f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				this->view_velocity.x += 2.0f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				this->view_velocity.y -= 2.0f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				this->view_velocity.y += 2.0f;
			
			this->view_velocity.x = std::min(16.0f, std::max(-16.0f, this->view_velocity.x));
			this->view_velocity.y = std::min(16.0f, std::max(-16.0f, this->view_velocity.y));
			
			this->view_velocity.x -= sign(this->view_velocity.x);
			this->view_velocity.y -= sign(this->view_velocity.y);
			
			sf::Vector2f current_viewpos = this->view.getCenter();
			current_viewpos += this->view_velocity;
			this->view.setCenter(current_viewpos);
			
			//Reset the window view
			this->window.setView(this->view);
			
			this->draw();
		}
	}
	
	void Game::draw()
	{
		this->window.clear(sf::Color::Blue);
		
		sf::Sprite tile;
		tile.setTexture(this->tileset);
		
		//Loop through the world
		Layer* visible_layer = &this->world.layers[this->current_layer];
		
		for (int i = 0; i < visible_layer->w; i ++)
		{
			for (int j = 0; j < visible_layer->h; j ++)
			{
				Cell* cell = visible_layer->get(i, j);
				
				sf::Vector2u pos = this->getTileRectangle(cell);
				tile.setTextureRect(sf::IntRect(pos.x, pos.y, 64.0f, 64.0f));
				tile.setPosition(sf::Vector2f(64.0f * i, 64.0f * j));
		
				this->window.draw(tile);
			}
		}
		
		this->window.display();
	}
	
	sf::Vector2u Game::getTileRectangle(Cell* cell)
	{
		switch(cell->type)
		{
			case CellType::EMPTY:
				return sf::Vector2u(0, 0);
				break;
			case CellType::FLOOR:
				return sf::Vector2u(128, 0);
				break;
			case CellType::WALL:
				return sf::Vector2u(128, 128);
				break;
			default:
				return sf::Vector2u(0, 0);
				break;
		}
	}
}
