#include "entity.h"

namespace MorningRitual
{
	Entity::Entity()
	{
		printf("Created entity\n");
	}
	
	void Entity::tick()
	{
		if (this->lifetime % 10 == 0 && this->path.size() > 0)
		{
			this->pos = this->path.pop();
		}
		
		this->lifetime ++;
	}
}
