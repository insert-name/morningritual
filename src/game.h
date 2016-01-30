#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

#include "world.h"
#include "gui.h"

namespace MorningRitual
{
	class Game
	{
		public:
			sf::RenderWindow window;
			
			sf::View view;
			sf::Vector2f view_velocity;
			
			sf::Texture tileset;
			
			World world;
			int current_layer = 0;
			
			GUI gui;
			
			Game();
			
			void run();
			void draw();
			sf::Vector2u getTileRectangle(Cell* cell);
	};
}

#endif
