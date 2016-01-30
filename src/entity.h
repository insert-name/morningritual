#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"

#include "common.h"
#include "path.h"

namespace MorningRitual
{
	class Game;
	
	enum EntityState
	{
		PATH,
		WANDER,
		STAND,
	};
	
	class Entity
	{
		public:
			glm::ivec3 pos;
			int lifetime = 0;
			EntityState state = EntityState::PATH;
			
			Path path;
			
			Entity();
			void tick(Game* game);
	};
}

#endif
