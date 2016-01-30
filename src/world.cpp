#include "stdio.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"

#include "world.h"
#include "common.h"

namespace MorningRitual
{	
	World::World()
	{
		printf("Created world\n");
		
		this->setup();
		this->load("Level 1");
	}
	
	void World::setup()
	{
		this->layers.clear();
	}
	
	void World::load(std::string levelname)
	{
		std::string data = this->loadFile(this->level_directory + "/" + levelname + "/lvl_0_root.txt");
		
		//printf(("The contents of the level file " + levelname + " is:\n" + data).c_str());
		
		std::vector<std::string> values = split(data, '\n');
		
		this->name = values[0];
		int w = std::stoi(values[1]);
		int h = std::stoi(values[2]);
		this->depth = std::stoi(values[3]);
		
		for (int i = 0; i < this->depth; i ++)
		{
			this->addLayer(w, h, this->loadFile(this->level_directory + "/" + levelname + "/" + values[4 + i]));
		}
		
	}
	
	void World::addLayer(int w, int h, std::string data)
	{
		this->layers.push_back(Layer());
		
		this->layers.back().w = w;
		this->layers.back().h = h;
		this->layers.back().setup();
		
		printf("Loading layer of size %dx%d\n", w, h);
		
		std::vector<std::string> rows = split(data, '\n');
		
		for (int j = 0; j < rows.size(); j ++)
		{
			for (int i = 0; i < rows[j].size(); i ++)
			{
				this->layers.back().set(i, j, rows[j][i]);
			}
			
			printf("Added layer row beginning with %c\n", rows[j][0]);
		}
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
