#include "stdio.h"

#include "world.h"

namespace MorningRitual
{
	void Layer::setup()
	{
		this->cells.clear();
		
		for (int i = 0; i < this->w; i ++)
		{
			for (int j = 0; j < this->h; j ++)
			{
				this->cells.push_back(Cell());
			}
		}
		
		printf("Created a layer of size %dx%d\n", this->w, this->h);
	}
	
	World::World()
	{
		printf("Created world\n");
		
		this->setup();
	}
	
	void World::setup()
	{
		this->layers.clear();
		
		for (int i = 0; i < this->depth; i ++)
		{
			this->layers.push_back(Layer());
			
			this->layers.back().setup();
		}
		
		printf("Created a world of depth %d\n", this->depth);
	}
}
