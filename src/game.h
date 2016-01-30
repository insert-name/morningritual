#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

#include "world.h"
#include "gui.h"
#include "soundmanager.h"

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
			SoundManager sound_manager;
			
			std::string data_directory = "../data";
			
			Game();
			
			void run();
			void draw();
			void drawEntities();
			sf::Vector2u getTileRectangle(Cell* cell);
	};
}

#endif
