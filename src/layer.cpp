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
				this->set(x, y, Cell(CellType::CT_WALL_X, 0));
				break;
			case '.':
				this->set(x, y, Cell(CellType::CT_WOOD_FLOOR, 0));
				break;
			case '~':
				this->set(x, y, Cell(CellType::CT_CARPET_FLOOR, 0));
				break;
			case '+':
				this->set(x, y, Cell(CellType::CT_DOOR_CLOSED, 0));
				break;
			case 't':
				this->set(x, y, Cell(CellType::CT_TABLE, 0));
				break;
			case 'T':
				this->set(x, y, Cell(CellType::CT_L_TOILET, 0));
				break;
			case 'W':
				this->set(x, y, Cell(CellType::CT_K_WCHINE, 0));
				break;
			case 'O':
				this->set(x, y, Cell(CellType::CT_K_OVEN, 0));
				break;
			case 's':
				this->set(x, y, Cell(CellType::CT_L_SINK, 0));
				break;
			case '<':
				this->set(x, y, Cell(CellType::CT_UPSTAIR, 0));
				break;
			case '>':
				this->set(x, y, Cell(CellType::CT_DOWNSTAIR, 0));
				break;
			case ' ':
				this->set(x, y, Cell());
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
