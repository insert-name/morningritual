#ifndef WORLD_H
#define WORLD_H

#include "vector"
#include "string"

#include "glm/glm.hpp"

#include "layer.h"
#include "path.h"
#include "entity.h"

namespace MorningRitual
{
	struct PathPoint
	{
		glm::ivec3 pos;
		int difficulty = 0;
		
		PathPoint(glm::ivec3 pos, int difficulty)
		{
			this->pos = pos;
			this->difficulty = difficulty;
		}
		
		bool operator==(const PathPoint& other)
		{
			if (this->pos == other.pos)
				return true;
			return false;
		}
	};
	
	class World
	{
		public:
			std::string name = "None";
			int depth = 0;
			std::vector<Layer> layers;
			std::string level_directory = "../data/levels";
			
			std::vector<Entity> entities;
			
			World();
			void setup();
			void tick();
			void load(std::string levelname);
			std::string loadFile(std::string filename);
			void addLayer(int w, int h, std::string data);
			
			Cell* get(glm::ivec3 p);
			
			Path findPath(glm::ivec3 p1, glm::ivec3 p2);
			bool canTraverse(glm::ivec3 p1, glm::ivec3 p2);
			std::vector<glm::ivec3> getMooreLocality(glm::ivec3 p);
	};
}

#endif
