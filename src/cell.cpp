#include "stdio.h"

#include "cell.h"
#include "world.h"

namespace MorningRitual
{
	bool Cell::isSolid()
	{
		return this->getGenericType() == CellGenericType::CGT_WALL;
	}
	
	void Cell::click(World* world)
	{
		printf("Clicked cell\n");
		
		if (this->getGenericType() == CellGenericType::CGT_DOOR)
		{
			this->id = CellType::CT_WOOD_FLOOR;
		}
	}
}
