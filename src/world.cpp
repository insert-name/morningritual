#include "stdio.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"
#include "deque"

#include "world.h"
#include "common.h"
#include "game.h"

namespace MorningRitual
{	
	World::World()
	{
		printf("Created world\n");
	}
	
	void World::setup()
	{
		this->layers.clear();
		
		this->load("Level 1");
		this->rotafyCells();
		
		this->entities.push_back(Entity());
		this->entities.back().pos = glm::ivec3(3, 1, 0);
		this->entities.back().path = this->findPath(glm::ivec3(3, 1, 0), glm::ivec3(6, 11, 0));
	}
	
	void World::tick(Game* game)
	{
		for (int i = 0; i < this->entities.size(); i ++)
		{
			entities[i].tick(game);
		}
	}
	
	void World::load(std::string levelname)
	{
		std::string data = this->loadFile(this->data_directory + "/levels/" + levelname + "/lvl_0_root.txt");
		
		//printf(("The contents of the level file " + levelname + " is:\n" + data).c_str());
		
		std::vector<std::string> values = split(data, '\n');
		
		this->name = values[0];
		int w = std::stoi(values[1]);
		int h = std::stoi(values[2]);
		this->depth = std::stoi(values[3]);
		
		for (int i = 0; i < this->depth; i ++)
		{
			this->addLayer(w, h, this->loadFile(this->data_directory + "/levels/" + levelname + "/" + values[4 + i]));
		}
		
	}
	
	void World::rotafyCells()
	{
		for (int z = 0; z < this->depth; z ++)
		{
			for (int x = 0; x < this->layers[z].w; x ++)
			{
				for (int y = 0; y < this->layers[z].h; y ++)
				{
					this->get(glm::ivec3(x, y, z))->self_mask = this->getCellRotationMask(glm::ivec3(x, y, z), (CellType)this->get(glm::ivec3(x, y, z))->id, 1);
					this->get(glm::ivec3(x, y, z))->solid_mask = this->getCellRotationMask(glm::ivec3(x, y, z), (CellType)this->get(glm::ivec3(x, y, z))->id, 0);
					this->get(glm::ivec3(x, y, z))->wall_mask = this->getCellRotationMask(glm::ivec3(x, y, z), (CellType)this->get(glm::ivec3(x, y, z))->id, 2);
					this->get(glm::ivec3(x, y, z))->furniture_mask = this->getCellRotationMask(glm::ivec3(x, y, z), (CellType)this->get(glm::ivec3(x, y, z))->id, 3);
				}
			}
		}
		
		printf("Rotafied world\n");
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
		
		if (p2.z < 0 || p2.z >= depth)
			return false;
		
		if (p1.z != p2.z)
		{
			int highest = std::max(p1.z, p2.z);
			int lowest = std::min(p1.z, p2.z);
			
			if (lowest < 0 || highest >= this->depth)
				return false;
			
			if (glm::ivec2(p1.x, p1.y) != glm::ivec2(p2.x, p2.y))
				return false;
			
				if (std::abs(highest - lowest) != 1)
				return false;
			
			if (this->get(glm::ivec3(p1.x, p1.y, lowest))->id != CellType::CT_UPSTAIR)
				return false;
				
			if (this->get(glm::ivec3(p1.x, p1.y, highest))->id != CellType::CT_DOWNSTAIR)
				return false;
		}
		
		if (p2.x < 0 || p2.y < 0 || p2.x >= this->layers[p2.z].w || p2.y >= this->layers[p2.z].h)
			return false;
		
		if (net <= 1)
		{
			if (this->get(p2)->getSolid())
				return false;
			else
				return true;
		}
		else
			return false;
	}
	
	std::vector<glm::ivec3> World::getMooreLocality(glm::ivec3 p, bool include_depth)
	{
		std::vector<glm::ivec3> locals;
		
		locals.push_back(glm::ivec3(p.x + 1, p.y + 0, p.z + 0));
		locals.push_back(glm::ivec3(p.x - 1, p.y + 0, p.z + 0));
		locals.push_back(glm::ivec3(p.x + 0, p.y + 1, p.z + 0));
		locals.push_back(glm::ivec3(p.x + 0, p.y - 1, p.z + 0));
		
		if (include_depth)
		{
			locals.push_back(glm::ivec3(p.x + 0, p.y + 0, p.z + 1));
			locals.push_back(glm::ivec3(p.x + 0, p.y + 0, p.z - 1));
		}
		
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
						//printf("Can traverse to %d,%d,%d\n", pos.x, pos.y, pos.z);
						
						if (!dequeContains<PathPoint>(open_set, PathPoint(pos, 0)) && !dequeContains<PathPoint>(closed_set, PathPoint(pos, 0)))
							open_set.push_back(PathPoint(pos, open_set.front().difficulty + 1));
					
						//printf("Point %d,%d,%d\n", pos.x, pos.y, pos.z);
						
						if (pos == p2)
						{
							found_path = true;
							break;
						}
					}
					else
					{
						//printf("Cannot traverse to %d,%d,%d\n", pos.x, pos.y, pos.z);
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
					if (this->canTraverse(locals[i], pos))
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
	
	glm::ivec3 World::findNearbyEmpty(glm::ivec3 pos)
	{
		std::vector<glm::ivec3> locals = this->getMooreLocality(pos, false);
		
		for (glm::ivec3 place : locals)
		{
			if (!this->get(place)->getSolid())
				return place;
		}
		
		return glm::ivec3(-1, -1, -1);
	}
	
	CellType World::getCellTypeAt(glm::ivec3 pos)
	{
		if (pos.z < 0 || pos.z >= this->depth)
			return CellType::CT_EMPTY;
		
		if (pos.x < 0 || pos.y < 0 || pos.x >= this->layers[pos.z].w || pos.y >= this->layers[pos.z].h)
			return CellType::CT_EMPTY;
		
		return (CellType)this->get(pos)->id;
	}
	
	int World::getCellRotationMask(glm::ivec3 pos, CellType type, int all_solid)
	{
		int mask = 0;
		
		if (all_solid == 0)
		{
			if (Cell(this->getCellTypeAt(pos + glm::ivec3(1, 0, 0)), 0).getSolid())
				mask |= 1;
			if (Cell(this->getCellTypeAt(pos + glm::ivec3(0, -1, 0)), 0).getSolid())
				mask |= 2;
			if (Cell(this->getCellTypeAt(pos + glm::ivec3(-1, 0, 0)), 0).getSolid())
				mask |= 4;
			if (Cell(this->getCellTypeAt(pos + glm::ivec3(0, 1, 0)), 0).getSolid())
				mask |= 8;
		}
		else if (all_solid == 1)
		{
			if (this->getCellTypeAt(pos + glm::ivec3(1, 0, 0)) == type)
				mask |= 1;
			if (this->getCellTypeAt(pos + glm::ivec3(0, -1, 0)) == type)
				mask |= 2;
			if (this->getCellTypeAt(pos + glm::ivec3(-1, 0, 0)) == type)
				mask |= 4;
			if (this->getCellTypeAt(pos + glm::ivec3(0, 1, 0)) == type)
				mask |= 8;
		}
		else if (all_solid == 2)
		{
			CellGenericType a = Cell(this->getCellTypeAt(pos + glm::ivec3(1, 0, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_WALL || a == CellGenericType::CGT_DOOR)
				mask |= 1;
			
			a = Cell(this->getCellTypeAt(pos + glm::ivec3(0, -1, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_WALL || a == CellGenericType::CGT_DOOR)
				mask |= 2;
			
			a = Cell(this->getCellTypeAt(pos + glm::ivec3(-1, 0, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_WALL || a == CellGenericType::CGT_DOOR)
				mask |= 4;
			
			a = Cell(this->getCellTypeAt(pos + glm::ivec3(0, 1, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_WALL || a == CellGenericType::CGT_DOOR)
				mask |= 8;
		}
		
		else if (all_solid == 3)
		{
			CellGenericType a = Cell(this->getCellTypeAt(pos + glm::ivec3(1, 0, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_FURNITURE)
				mask |= 1;
			
			a = Cell(this->getCellTypeAt(pos + glm::ivec3(0, -1, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_FURNITURE)
				mask |= 2;
			
			a = Cell(this->getCellTypeAt(pos + glm::ivec3(-1, 0, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_FURNITURE)
				mask |= 4;
			
			a = Cell(this->getCellTypeAt(pos + glm::ivec3(0, 1, 0)), 0).getGenericType();
			if (a == CellGenericType::CGT_FURNITURE)
				mask |= 8;
		}
		
		return mask;
	}
}
