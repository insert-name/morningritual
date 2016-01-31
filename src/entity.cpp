#include "stdlib.h"

#include "entity.h"
#include "game.h"

namespace MorningRitual
{
	Entity::Entity()
	{
		printf("Created entity\n");
		
		this->tasks.push_back(TaskType::TT_SHOWER);
		this->tasks.push_back(TaskType::TT_COOK_FOOD);
		this->tasks.push_back(TaskType::TT_FIND_FOOD);
		this->tasks.push_back(TaskType::TT_WASH_PLATES);
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
						else if (this->path.success)
						{
							this->tasks.pop_back();
							this->path = game->world.findPath(this->pos, game->world.findNearbyEmpty(this->findTaskTarget(&game->world, this->tasks.back())));
						}
						else
						{
							this->state = EntityState::WANDER;
						}
					}
					break;
				
				case EntityState::WANDER:
					if (this->lifetime % 40 == 0)
						this->wander_direction = glm::ivec3(rand() % 3 - 1, rand() % 3 - 1, 0);
					if (this->lifetime % 20 == 0)
					{
						this->moveTo(this->pos + this->wander_direction, &game->world);
					}
					
					if (this->lifetime % 60 == 0 && this->tasks.size() > 0)
					{
						this->path = game->world.findPath(this->pos, game->world.findNearbyEmpty(this->findTaskTarget(&game->world, this->tasks.back())));
						if (this->path.success)
							this->state = EntityState::PATH;
					}
					
					break;
					
				default:
					break;
						
			}
		}
		
		this->lifetime ++;
	}
	
	glm::ivec3 Entity::findTaskTarget(World* world, TaskType type)
	{
		CellType cell_find;
		
		switch(type)
		{
			case TaskType::TT_BRUSH_TEETH:
				cell_find = CellType::CT_L_SINK;
				break;
			case TaskType::TT_COOK_FOOD:
				cell_find = CellType::CT_K_OVEN;
				break;
			case TaskType::TT_FIND_FOOD:
				cell_find = CellType::CT_K_FRIDGE;
				break;
			case TaskType::TT_SHOWER:
				cell_find = CellType::CT_L_SHOWER;
				break;
			
			case TaskType::TT_WASH_PLATES:
				cell_find = CellType::CT_K_SINK;
				break;
		}
		
		for (int z = 0; z < world->depth; z ++)
		{
			for (int x = 0; x < world->layers[z].w; x ++)
			{
				for (int y = 0; y < world->layers[z].h; y ++)
				{
					if (world->get(glm::ivec3(x, y, z))->id == cell_find)
						return glm::ivec3(x, y, z);
				}
			}
		}
		
		return glm::ivec3(-1, -1, -1);
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
