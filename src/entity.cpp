#include "entity.h"
#include "game.h"

namespace MorningRitual
{
	Entity::Entity()
	{
		printf("Created entity\n");
	}
	
	void Entity::tick(Game* game)
	{
		if (this->lifetime % 10 == 0 && this->state == EntityState::PATH)
		{
			if (this->path.size() > 0)
				this->pos = this->path.pop();
			else
			{
				game->gui.notify("Finished pathing", this->pos);
				this->state = EntityState::STAND;
			}
		}
		
		this->lifetime ++;
	}
}
