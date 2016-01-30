#ifndef LAYER_H
#define LAYER_H

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
			void set(int x, int y, char cell);
			void set(int x, int y, Cell cell);
	};
}

#endif
