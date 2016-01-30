#ifndef PATH_H
#define PATH_H

#include "vector"

#include "SFML/Graphics.hpp"

namespace MorningRitual
{
	struct Path
	{
		bool success = false;
		std::vector<sf::Vector2u> points;
		
		void push(sf::Vector2u point) { this->points.push_back(point); }
		sf::Vector2u pop() { sf::Vector2u a = this->points.back(); this->points.pop_back(); return a; }
	};
}

#endif
