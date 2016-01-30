#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

#include "world.h"

namespace MorningRitual
{
	class Game
	{
		public:
			sf::RenderWindow window;
			
			World world;
			Game();
			
			void run();
			void draw();
	};
}

#endif
