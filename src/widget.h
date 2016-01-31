#ifndef WIDGET_H
#define WIDGET_H

#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"

namespace MorningRitual
{
	class Game;
	
	class Widget
	{
		public:
			sf::Vector2f position;
			int lifetime = 0;
			int startlife = -1;
			int alpha = 255;
			sf::Texture texture;
			std::string message = "NONE";
			glm::ivec3 notify_pos = glm::ivec3(-1, -1, -1);
			bool decay = true;
			
			sf::Color font_colour = sf::Color::Black;
			int font_size = 32;
			bool font_bold = false;
			
			void tick();
			void click(Game* game);
	};
}

#endif
