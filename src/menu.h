#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"

namespace MorningRitual
{
	enum MenuItemType
	{
		BUTTON,
		LINEAR,
		TOGGLE,
	};
	
	struct MenuItem
	{
		MenuItemType type;
		sf::Texture tex;
		sf::Vector2f position;
		sf::Vector2f size;
		
		int action = 0;
	};
	
	class Menu
	{
		public:
			sf::Texture back_tex;
			
			std::vector<MenuItem> menu_items;
			int selected_item = 0;
			
			sf::Color unselect_color = sf::Color(120, 80, 40);
			
			int run(sf::RenderWindow* window)
			{
				while (window->isOpen())
				{
					sf::Event event;
					while (window->pollEvent(event))
					{
						switch(event.type)
						{
							case sf::Event::Closed:
								window->close();
								return 1337;
								break;
					
							case sf::Event::KeyPressed:
								if (event.key.code == sf::Keyboard::Key::Return)
									return this->menu_items[this->selected_item].action;
								if (event.key.code == sf::Keyboard::Key::Up)
									selected_item = (selected_item - 1 + this->menu_items.size()) % this->menu_items.size();
								if (event.key.code == sf::Keyboard::Key::Down)
									selected_item = (selected_item + 1 + this->menu_items.size()) % this->menu_items.size();
								break;
					
							default:
								break;
						}
					}
					
					window->clear(sf::Color(50, 15, 15));
		
					sf::Sprite back;
					
					back.setTexture(this->back_tex);
					sf::Vector2u a = this->back_tex.getSize();
					back.setPosition(sf::Vector2f(400, 300) - sf::Vector2f(a.x / 2, a.y / 2));
					//back.setScale(sf::Vector2f(0.5f, 0.5f));
					
					window->draw(back);
					
					for (int i = 0; i < this->menu_items.size(); i ++)
					{
						sf::Sprite item;
						
						item.setTexture(this->menu_items[i].tex);
						item.setPosition(this->menu_items[i].position);
						
						if (i != this->selected_item)
							item.setColor(this->unselect_color);
						
						window->draw(item);
					}
		
					window->display();
				}
			}
	};
}

#endif
