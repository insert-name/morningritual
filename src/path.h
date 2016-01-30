#ifndef PATH_H
#define PATH_H

#include "vector"

#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"

namespace MorningRitual
{
	struct Path
	{
		bool success = false;
		std::vector<glm::ivec3> points;
		
		void push(glm::ivec3 point) { this->points.push_back(point); }
		glm::ivec3 pop() { glm::ivec3 a = this->points.back(); this->points.pop_back(); return a; }
		int size() { return this->points.size(); }
	};
}

#endif
