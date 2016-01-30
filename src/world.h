#ifndef WORLD_H
#define WORLD_H

#include "vector"
#include "string"

#include "layer.h"

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
	};
}

#endif
