#include "stdio.h"

#include "cell.h"
#include "world.h"

namespace MorningRitual
{
	bool Cell::isSolid()
	{
		return this->solid;
	}
	
	void Cell::click(World* world)
	{
		printf("Clicked cell\n");
		
		if (this->type == CellType::CT_DOOR)
		{
			this->type = CellType::CT_FLOOR;
		}
	}
}
