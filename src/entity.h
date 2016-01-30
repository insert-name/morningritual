#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"

#include "common.h"
#include "path.h"

namespace MorningRitual
{
	class Entity
	{
		public:
			glm::ivec3 pos;
			int lifetime = 0;
			
			Path path;
			
			Entity();
			void tick();
	};
}

#endif
