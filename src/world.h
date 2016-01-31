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
			std::string data_directory;
			
			std::vector<Entity> entities;
			
			int time = 0;
			int timeleft = 0;
			
			std::vector<std::string> level_list;
			int level_id = 0;
			
			World();
			void setup();
			void tick(Game* game);
			void load(std::string levelname);
			std::string loadFile(std::string filename);
			void addLayer(int w, int h, std::string data);
			
			void rotafyCells();
			
			Cell* get(glm::ivec3 p);
			
			Path findPath(glm::ivec3 p1, glm::ivec3 p2);
			bool canTraverse(glm::ivec3 p1, glm::ivec3 p2);
			std::vector<glm::ivec3> getMooreLocality(glm::ivec3 p, bool include_depth = true);
			glm::ivec3 findNearbyEmpty(glm::ivec3 pos);
			
			CellType getCellTypeAt(glm::ivec3 pos);
			int getCellRotationMask(glm::ivec3 pos, CellType type, int all_solid);
	};
}

#endif
