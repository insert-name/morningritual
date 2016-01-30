#include "stdio.h"
#include "iostream"
#include "sstream"
#include "fstream"

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
		this->load("0");
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
	
	void World::load(std::string levelname)
	{
		std::string data = this->loadFile(this->level_directory + "/lvl_" + levelname + "_root.txt");
		
		printf(("The contents of the level file " + levelname + " is:\n" + data).c_str());
		
		
	}
	
	std::string World::loadFile(std::string filename)
	{
		std::ifstream file;
		file.open(filename.c_str());
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}
}
