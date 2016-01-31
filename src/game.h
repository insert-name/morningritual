#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"

#include "world.h"
#include "gui.h"
#include "soundmanager.h"

namespace MorningRitual
{
	enum ViewState
	{
		FREE,
		MOVETO,
		LOCKED,
	};
	
	class Game
	{
		public:
			sf::RenderWindow window;
			
			sf::View view;
			sf::Vector2f view_velocity;
			sf::Vector2f view_target;
			ViewState view_state = ViewState::FREE;
			
			bool playing = true;
			
			sf::Texture tileset;
			sf::Font mainfont;
			
			bool mouse_down = false;
			glm::vec2 mouse_old_pos;
			
			World world;
			int current_layer = 0;
			
			GUI gui;
			
			std::string data_directory = "../data";
			
			Game();
			
			void run();
			void draw();
			void drawEntities();
			void drawGUI();
			sf::Vector2u getTileRectangle(Cell* cell);
			
			void mouseClick(sf::Event event);
			void mouseRelease(sf::Event event);
			void mouseScroll(sf::Event event);
			
			void moveTo(glm::ivec3 pos);
	};
}

#endif
