#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"

#include "common.h"
#include "path.h"

namespace MorningRitual
{
	class Game;
	class World;
	
	enum EntityState
	{
		PATH,
		WANDER,
		STAND,
		TASK,
	};
	
	enum TaskType
	{
		TT_BRUSH_TEETH,
		TT_FIND_FOOD,
		TT_COOK_FOOD,
		TT_SHOWER,
		TT_WASH_PLATES,
	};
	
	class Entity
	{
		public:
			glm::ivec3 pos;
			int lifetime = 0;
			EntityState state = EntityState::PATH;
			glm::ivec3 wander_direction = glm::ivec3(0, 0, 0);
			std::string name = "<Name>";
			
			std::vector<TaskType> tasks;
			
			glm::ivec3 findTaskTarget(World* world, TaskType type);
			
			Path path;
			
			Entity();
			void tick(Game* game);
			bool moveTo(glm::ivec3 pos, World* world);
	};
}

#endif
