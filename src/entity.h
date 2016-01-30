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
		BRUSH_TEETH,
		FIND_FOOD,
	};
	
	class Entity
	{
		public:
			glm::ivec3 pos;
			int lifetime = 0;
			EntityState state = EntityState::PATH;
			glm::ivec3 wander_direction = glm::ivec3(0, 0, 0);
			
			std::vector<TaskType> tasks;
			
			Path path;
			
			Entity();
			void tick(Game* game);
			void moveTo(glm::ivec3 pos, World* world);
	};
}

#endif
