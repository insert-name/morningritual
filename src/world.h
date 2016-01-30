#ifndef WORLD_H
#define WORLD_H

#include "vector"
#include "string"

#include "layer.h"
#include "path.h"

namespace MorningRitual
{
	class World
	{
		public:
			std::string name = "None";
			int depth = 0;
			std::vector<Layer> layers;
			std::string level_directory = "../data/levels";
			
			World();
			void setup();
			void load(std::string levelname);
			std::string loadFile(std::string filename);
			void addLayer(int w, int h, std::string data);
			
			Cell* get(int x, int y, int z);
			
			Path findPath(int x1, int y1, int z1, int x2, int y2, int z2);
			bool canTraverse(int x1, int y1, int z1, int x2, int y2, int z2);
	};
}

#endif
