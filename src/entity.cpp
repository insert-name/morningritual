#include "stdlib.h"

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
		if (this->lifetime % 10 == 0)
		{
			switch(this->state)
			{
				case EntityState::PATH:
					if (this->path.size() > 0)
					{
						bool moved = this->moveTo(this->path.pop(), &game->world);
						
						if (!moved)
						{
							this->path.success = false;
							this->state = EntityState::WANDER;
							game->gui.notify(this->name + " cannot reach destination", this->pos);
						}
					}
					else
					{
						game->gui.notify(this->name + " has finished walking", this->pos);
				
						if (this->tasks.size() == 0)
							this->state = EntityState::WANDER;
						else
							this->state = EntityState::STAND;
					}
					break;
				
				case EntityState::WANDER:
					if (this->lifetime % 40 == 0)
						this->wander_direction = glm::ivec3(rand() % 3 - 1, rand() % 3 - 1, 0);
					if (this->lifetime % 20 == 0)
					{
						this->moveTo(this->pos + this->wander_direction, &game->world);
					}
					break;
					
				default:
					break;
						
			}
		}
		
		this->lifetime ++;
	}
	
	bool Entity::moveTo(glm::ivec3 pos, World* world)
	{
		if (world->canTraverse(this->pos, pos))
		{
			this->pos = pos;
			return true;
		}
		return false;
	}
}
