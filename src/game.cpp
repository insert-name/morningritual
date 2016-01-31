#include "stdio.h"
#include "string"
#include "iomanip"

#include "game.h"
#include "common.h"
#include "menu.h"

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
		
		this->tileset.loadFromFile(this->data_directory + "/tiles/tileSet1-01.png");
		
		printf("Opened tileset\n");
		
		//Setup GUI
		this->gui.data_directory = this->data_directory;
		this->gui.setup();
		
		//Setup world
		this->world.data_directory = this->data_directory;
		this->world.setup();
		
		//Find the right font
		this->mainfont.loadFromFile(this->data_directory + "/fonts/ENYO_Serif_light.ttf");
		
		Menu main_menu;
		main_menu.back_tex.loadFromFile(this->data_directory + "/GUI/01 title menu.png");
		
		main_menu.menu_items.push_back(MenuItem());
		main_menu.menu_items.back().tex.loadFromFile(this->data_directory + "/GUI/title menu start game btn.png");
		main_menu.menu_items.back().position = sf::Vector2f(338, 372);
		main_menu.menu_items.back().action = 9001;
		
		main_menu.menu_items.push_back(MenuItem());
		main_menu.menu_items.back().tex.loadFromFile(this->data_directory + "/GUI/title menu options btn.png");
		main_menu.menu_items.back().position = sf::Vector2f(360, 428);
		main_menu.menu_items.back().action = 9002;
		
		main_menu.menu_items.push_back(MenuItem());
		main_menu.menu_items.back().tex.loadFromFile(this->data_directory + "/GUI/title menu exit game btn.png");
		main_menu.menu_items.back().position = sf::Vector2f(342, 486);
		main_menu.menu_items.back().action = 1337;
		
		Menu options_menu;
		options_menu.back_tex.loadFromFile(this->data_directory + "/GUI/01 title menu.png");
		
		options_menu.menu_items.push_back(MenuItem());
		options_menu.menu_items.back().tex.loadFromFile(this->data_directory + "/GUI/options menu BGM btn.png");
		options_menu.menu_items.back().position = sf::Vector2f(382, 372);
		options_menu.menu_items.back().action = 1;
		
		options_menu.menu_items.push_back(MenuItem());
		options_menu.menu_items.back().tex.loadFromFile(this->data_directory + "/GUI/options menu SFX btn.png");
		options_menu.menu_items.back().position = sf::Vector2f(384, 428);
		options_menu.menu_items.back().action = 2;
		
		options_menu.menu_items.push_back(MenuItem());
		options_menu.menu_items.back().tex.loadFromFile(this->data_directory + "/GUI/options menu back btn.png");
		options_menu.menu_items.back().position = sf::Vector2f(378, 486);
		options_menu.menu_items.back().action = 3;
		
		int result;
		int state = 0;
		
		while (true)
		{
			if (state == 0)
				result = main_menu.run(&this->window);
			else
				result = options_menu.run(&this->window);
			
			if (result == 1337)
			{
				this->playing = false;
				break;
			}
			else if (result == 9001)
			{
				//TO THE GAME!
				break;
			}
			else if (result == 9002)
			{
				state = 1;
			}
			else if (result == 1)
			{
				//BACKGROUND MUSIC
				this->gui.sound_manager.back_muted ^= true;
				this->gui.sound_manager.update();
			}
			else if (result == 2)
			{
				//SOUND
				this->gui.sound_manager.sound_muted ^= true;
				this->gui.sound_manager.update();
			}
			else if (result == 3)
			{
				state = 0;
			}
		}
	}
	
	void Game::run()
	{
		printf("Running game...\n");
		
		while (this->window.isOpen() && this->playing)
		{
			sf::Event event;
			while (this->window.pollEvent(event))
			{
				switch(event.type)
				{
					case sf::Event::Closed:
						this->window.close();
						break;
					
					case sf::Event::KeyPressed:
						if (event.key.code == sf::Keyboard::Key::Comma)
							this->current_layer = std::min(this->world.depth - 1, std::max(0, this->current_layer + 1));
						if (event.key.code == sf::Keyboard::Key::Period)
							this->current_layer = std::min(this->world.depth - 1, std::max(0, this->current_layer - 1));
						break;
					
					case sf::Event::MouseButtonPressed:
						this->mouseClick(event);
						break;
					
					case sf::Event::MouseButtonReleased:
						this->mouseRelease(event);
						break;
					
					case sf::Event::MouseWheelScrolled:
						this->mouseScroll(event);
						break;
					
					default:
						break;
				}
			}
			
			sf::Vector2f current_viewpos = this->view.getCenter();
			
			if (this->view_state == ViewState::FREE)
			{
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
				
				if (this->mouse_down)
				{
					current_viewpos.x += -(sf::Mouse::getPosition(this->window).x - this->mouse_old_pos.x) * 1.0f;
					current_viewpos.y += -(sf::Mouse::getPosition(this->window).y - this->mouse_old_pos.y) * 1.0f;
					
					this->mouse_old_pos = glm::ivec2(sf::Mouse::getPosition(this->window).x, sf::Mouse::getPosition(this->window).y);
				}
			
				this->view_velocity.x -= sign(this->view_velocity.x);
				this->view_velocity.y -= sign(this->view_velocity.y);
				
				if (std::sqrt(this->view_velocity.x * this->view_velocity.x + this->view_velocity.y * this->view_velocity.y) < 0.5f)
					this->view_velocity = sf::Vector2f(0.0f, 0.0f);
			}
			else if (this->view_state == ViewState::MOVETO)
			{
				sf::Vector2f offset = this->view_target - this->view.getCenter();
				
				this->view_velocity = offset * 0.05f;
				
				if (std::sqrt(offset.x * offset.x + offset.y * offset.y) < 4.0f)
				{
					this->view_state = ViewState::FREE;
				}
			}
			
			current_viewpos += this->view_velocity;
			this->view.setCenter(current_viewpos);
			
			//Reset the window view
			this->window.setView(this->view);
			
			//Tick the world
			this->world.tick(this);
			
			//Tick the GUI
			this->gui.tick();
			//Update timer text
			std::stringstream ss;
			ss << std::floor(this->world.time / 6.0f) / 10.0f;
			this->gui.permanent[0].message = "";
			for (int i = 0; i < 6 - ss.str().size(); i ++) this->gui.permanent[0].message += " ";
			this->gui.permanent[0].message += "        " + ss.str();
			
			this->draw();
		}
	}
	
	void Game::draw()
	{
		this->window.clear(sf::Color(50, 200, 50));
		
		sf::Sprite tile;
		tile.setTexture(this->tileset);
		
		//Loop through the world
		Layer* visible_layer = &this->world.layers[this->current_layer];
		
		for (int i = 0; i < visible_layer->w; i ++)
		{
			for (int j = 0; j < visible_layer->h; j ++)
			{
				Cell* cell = visible_layer->get(i, j);
				
				sf::Vector2u pos = (this->getTileRectangle(cell) + cell->getTexOffset()) * (unsigned int)64;
				tile.setTextureRect(sf::IntRect(pos.x, pos.y, 64, 64));
				tile.setPosition(sf::Vector2f(64.0f * i, 64.0f * j));
		
				this->window.draw(tile);
			}
		}
		
		this->drawEntities();
		
		this->drawGUI();
		
		this->window.display();
	}
	
	void Game::drawEntities()
	{
		for (Entity entity : this->world.entities)
		{
			sf::Sprite tile;
			tile.setTexture(this->tileset);
			
			tile.setTextureRect(sf::IntRect(8 * 64, 10 * 64, 64, 64));
			tile.setPosition(sf::Vector2f(entity.pos.x * 64, entity.pos.y * 64));
			
			sf::RectangleShape tile2;
			tile2.setSize(sf::Vector2f(64, 64));
			
			//for (
			//tile2.setPosition(sf::Vector2f());
			
			if (entity.pos.z == this->current_layer)
				this->window.draw(tile);
		}
	}
	
	void Game::drawGUI()
	{
		for (int i = 0; i < this->gui.notification_widgets.size(); i ++)
		{
			Widget* widget = &this->gui.notification_widgets[i];
			
			sf::Sprite component;
			component.setTexture(widget->texture);
			component.setPosition(this->view.getCenter() - this->view.getSize() / 2.0f + widget->position);
			component.setColor(sf::Color(255, 255, 255, widget->alpha));
			
			this->window.draw(component);
			
			sf::Text message;
			message.setPosition(this->view.getCenter() - this->view.getSize() / 2.0f + sf::Vector2f(widget->position.x + 16, widget->position.y + 8));
			message.setFont(this->mainfont);
			message.setString(widget->message);
			message.setCharacterSize(32);
			message.setStyle(sf::Text::Bold);
			message.setColor(sf::Color::Black);
			
			window.draw(message);
		}
		
		for (int i = 0; i < this->gui.permanent.size(); i ++)
		{
			Widget* widget = &this->gui.permanent[i];
			
			sf::Sprite component;
			component.setTexture(widget->texture);
			component.setPosition(this->view.getCenter() - this->view.getSize() / 2.0f + widget->position);
			component.setColor(sf::Color(255, 255, 255, widget->alpha));
			
			this->window.draw(component);
			
			sf::Text message;
			message.setPosition(this->view.getCenter() - this->view.getSize() / 2.0f + sf::Vector2f(widget->position.x + 16, widget->position.y + 8));
			message.setFont(this->mainfont);
			message.setString(widget->message);
			message.setCharacterSize(32);
			message.setStyle(sf::Text::Bold);
			message.setColor(sf::Color::Black);
			
			window.draw(message);
		}
	}
	
	sf::Vector2u Game::getTileRectangle(Cell* cell)
	{
		switch(cell->id)
		{
			/*case CellType::CT_EMPTY:
				return sf::Vector2u(0, 0);
				break;
			case CellType::CT_FLOOR:
				switch (cell->variant)
				{
					case 0:
						return sf::Vector2u(1, 0);
						break;
					case 1:
						return sf::Vector2u(1, 2);
						break;
					default:
						return sf::Vector2u(0, 0);
						break;
				}
				break;
			case CellType::CT_FURNITURE:
				switch (cell->variant)
				{
					case 0:
						return sf::Vector2u(1, 1);
						break;
					case 1:
						return sf::Vector2u(7, 1);
						break;
					case 2:
						return sf::Vector2u(2, 4);
						break;
					case 3:
						return sf::Vector2u(0, 3);
						break;
					case 4:
						return sf::Vector2u(3, 1);
						break;
					default:
						return sf::Vector2u(0, 0);
						break;
				}
				break;
			case CellType::CT_DOOR:
				return sf::Vector2u(7, 0);
				break;
			case CellType::CT_WALL:
				return sf::Vector2u(2, 0);
				break;
			case CellType::CT_UPSTAIR:
				return sf::Vector2u(0, 1);
				break;
			case CellType::CT_DOWNSTAIR:
				return sf::Vector2u(0, 2);
				break;*/
			default:
				return cell->getTexCoords();
				break;
		}
	}
	
	void Game::mouseClick(sf::Event event)
	{
		switch (event.mouseButton.button)
		{
			case sf::Mouse::Button::Left:
			{
				printf("Left click mouse event at %d, %d\n", event.mouseButton.x, event.mouseButton.y);
				
				bool caught_event = false;
				
				//Check for GUI first
				for (int i = 0; i < this->gui.notification_widgets.size(); i ++)
				{
					Widget* widget = &this->gui.notification_widgets[i];
					
					if (event.mouseButton.x > widget->position.x && event.mouseButton.y > widget->position.y)
					{
						if (event.mouseButton.x < widget->position.x + widget->texture.getSize().x && event.mouseButton.y < widget->position.y + widget->texture.getSize().y)
						{
							printf("Mouse click hit widget\n");
							
							caught_event = true;
							
							widget->click(this);
						}
					}
				}
				
				if (!caught_event)
				{
					//Check cells
					glm::ivec2 click_pos;
					
					click_pos.x = (event.mouseButton.x + this->view.getCenter().x - this->view.getSize().x / 2.0f) / 64;
					click_pos.y = (event.mouseButton.y + this->view.getCenter().y - this->view.getSize().y / 2.0f) / 64;
					
					if (click_pos.x >= 0 && click_pos.y >= 0 && click_pos.x < this->world.layers[this->current_layer].w && click_pos.y < this->world.layers[this->current_layer].h)
					{
						//It's inside the world
						this->world.layers[this->current_layer].get(click_pos.x, click_pos.y)->click(this);
					}
				}
			}
				break;
			
			case sf::Mouse::Button::Right:
				this->mouse_down = true;
				this->mouse_old_pos = glm::vec2(event.mouseButton.x, event.mouseButton.y);
				break;
		}
	}
	
	void Game::mouseRelease(sf::Event event)
	{
		switch (event.mouseButton.button)
		{
			case sf::Mouse::Button::Right:
				this->mouse_down = false;
				break;
		}
	}
	
	void Game::mouseScroll(sf::Event event)
	{
		printf("Scrolled mouse wheel\n");
	}
	
	void Game::moveTo(glm::ivec3 pos)
	{
		this->current_layer = pos.z;
		this->view_target = sf::Vector2f(pos.x, pos.y) * 64.0f;
		this->view_state = ViewState::MOVETO;
	}
}
