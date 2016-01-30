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
	
	void Layer::set(int x, int y, Cell cell)
	{
		this->cells[x * this->h + y] = cell;
	}
	
	void Layer::set(int x, int y, char cell)
	{
		switch (cell)
		{
			case '#':
				this->set(x, y, Cell(CellType::WALL, 0, true, 0));
				break;
			case '.':
				this->set(x, y, Cell(CellType::FLOOR, 0, false, 0));
				break;
			default:
				this->set(x, y, Cell());
				break;
		}
	}
	
	Cell* Layer::get(int x, int y)
	{
		return &this->cells[x * this->h + y];
	}
}
