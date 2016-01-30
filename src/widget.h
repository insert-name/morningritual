#ifndef WIDGET_H
#define WIDGET_H

#include "SFML/Graphics.hpp"

namespace MorningRitual
{
	class Widget
	{
		public:
			sf::Vector2f position;
			int lifetime = 0;
			sf::Texture tex;
	};
}

#endif
