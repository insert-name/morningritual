#include "vector"
#include "string"

#include "cell.h"

namespace MorningRitual
{
	struct Layer
	{
		public:
			int w = 16;
			int h = 16;
			std::vector<Cell> cells;
			
			void setup();
	};
	
	class World
	{
		public:
			std::string name = "None";
			int depth = 2;
			std::vector<Layer> layers;
			std::string level_directory = "../data/levels";
			
			World();
			void setup();
			void load(std::string levelname);
			std::string loadFile(std::string filename);
			void addLayer(int w, int h, std::string data);
	};
}
