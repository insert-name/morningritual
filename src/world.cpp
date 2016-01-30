#include "stdio.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"
#include "deque"

#include "world.h"
#include "common.h"

namespace MorningRitual
{	
	World::World()
	{
		printf("Created world\n");
		
		this->setup();
		this->load("Level 1");
		
		this->entities.push_back(Entity());
		this->entities.back().pos = glm::ivec3(3, 1, 0);
		this->entities.back().path = this->findPath(glm::ivec3(3, 1, 0), glm::ivec3(14, 3, 0));
	}
	
	void World::setup()
	{
		this->layers.clear();
	}
	
	void World::tick()
	{
		for (int i = 0; i < this->entities.size(); i ++)
		{
			entities[i].tick();
		}
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
	
	Cell* World::get(glm::ivec3 p)
	{
		return this->layers[p.z].get(p.x, p.y);
	}
	
	bool World::canTraverse(glm::ivec3 p1, glm::ivec3 p2)
	{
		int net = std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y) + std::abs(p1.z - p2.z);
		
		if (p1.z != p2.z)
			return false;
		
		if (p2.z < 0 || p2.z >= this->layers.size())
			return false;
		printf("HELLO!\n");
		if (p2.x < 0 || p2.y < 0 || p2.x >= this->layers[p2.z].w || p2.y >= this->layers[p2.z].h)
			return false;
		printf("HELLO  %d\n", net);
		
		if (net == 0)
			return true;
		else if (net == 1)
		{
			if (this->get(p2)->solid == true)
				return false;
			else
				return true;
		}
		else
			return false;
	}
	
	std::vector<glm::ivec3> World::getMooreLocality(glm::ivec3 p)
	{
		std::vector<glm::ivec3> locals;
		
		locals.push_back(glm::ivec3(p.x + 1, p.y + 0, p.z + 0));
		locals.push_back(glm::ivec3(p.x - 1, p.y + 0, p.z + 0));
		locals.push_back(glm::ivec3(p.x + 0, p.y + 1, p.z + 0));
		locals.push_back(glm::ivec3(p.x + 0, p.y - 1, p.z + 0));
		locals.push_back(glm::ivec3(p.x + 0, p.y + 0, p.z + 1));
		locals.push_back(glm::ivec3(p.x + 0, p.y + 0, p.z - 1));
		
		return locals;
	}
	
	Path World::findPath(glm::ivec3 p1, glm::ivec3 p2)
	{
		std::deque<PathPoint> open_set;
		std::deque<PathPoint> closed_set;
		
		bool found_path = false;
		
		open_set.push_back(PathPoint(p1, 0));
		
		while (open_set.size() > 0 && found_path == false)
		{
			int set_size = open_set.size();
			
			for (int i = 0; i < set_size; i ++)
			{
				std::vector<glm::ivec3> locals = this->getMooreLocality(open_set.front().pos);
				
				for (glm::ivec3 pos : locals)
				{
					if (this->canTraverse(open_set.front().pos, pos))
					{
						printf("Can traverse to %d,%d,%d\n", pos.x, pos.y, pos.z);
						
						if (!dequeContains<PathPoint>(open_set, PathPoint(pos, 0)) && !dequeContains<PathPoint>(closed_set, PathPoint(pos, 0)))
							open_set.push_back(PathPoint(pos, open_set.front().difficulty + 1));
					
						printf("Point %d,%d,%d\n", pos.x, pos.y, pos.z);
						if (pos == p2)
						{
							found_path = true;
							break;
						}
					}
					else
					{
						printf("Cannot traverse to %d,%d,%d\n", pos.x, pos.y, pos.z);
					}
				}
				
				closed_set.push_back(open_set.front());
				open_set.pop_front();
			}
		}
		
		for (PathPoint pos : open_set)
			closed_set.push_back(pos);
		
		if (found_path)
		{
			printf("FOUND PATH!\n");
			
			//Reassemble path
			glm::ivec3 pos = p2;
			
			Path path;
			path.success = true;
			path.push(p2);
			
			while (pos != p1)
			{
				//Find moore neighbourhood
				std::vector<glm::ivec3> locals = this->getMooreLocality(pos);
				
				int lowest = 100000000000;
				glm::ivec3 newpos;
				
				for (int i = 0; i < locals.size(); i ++)
				{
					int j = dequeAt<PathPoint>(closed_set, PathPoint(locals[i], 0));
					
					if (j != -1)
					{
						if (closed_set[j].difficulty < lowest)
						{
							lowest = closed_set[j].difficulty;
							newpos = closed_set[j].pos;
						}
					}
				}
				
				pos = newpos;
				path.push(pos);
			}
			
			return path;
		}
		else
		{
			printf("COULDN'T FIND PATH!\n");
			
			Path p;
			p.success = false;
			return p;
		}
		
		
	}
}
