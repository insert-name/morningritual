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
			int depth = 2;
			std::vector<Layer> layers;
			std::string level_directory = "levels";
			
			World();
			void setup();
			void loadFile(std::string levelname);
	};
}
