#include "stdio.h"

#include "cell.h"
#include "world.h"

namespace MorningRitual
{
	void Cell::click(World* world)
	{
		printf("Clicked cell\n");
		
		if (this->id == CellType::CT_DOOR_CLOSED)
		{
			this->id = CellType::CT_DOOR_OPEN;
		}
		else if (this->id == CellType::CT_DOOR_OPEN)
		{
			this->id = CellType::CT_DOOR_CLOSED;
		}
	}
	
	bool Cell::getSolid() 
	{
		switch (this->id)
		{
			case CellType::CT_EMPTY:
			case CellType::CT_POND:

			case CellType::CT_WALL_H:
			case CellType::CT_WALL_C:
			case CellType::CT_WALL_T:
			case CellType::CT_WALL_X:
			case CellType::CT_WINDOW_SMALL:
			case CellType::CT_WINDOW_LARGE_L:
			case CellType::CT_WINDOW_LARGE_R:

			case CellType::CT_DOOR_CLOSED:

			case CellType::CT_K_COUNTER_STRAIGHT:
			case CellType::CT_K_COUNTER_INNER:
			case CellType::CT_K_COUNTER_OUTER:
			case CellType::CT_K_OVEN:
			case CellType::CT_K_FRIDGE:
			case CellType::CT_K_WCHINE:
			case CellType::CT_K_SINK:

			case CellType::CT_B_WARDROBE_L:
			case CellType::CT_B_WARDROBE_R:
				return true;
				break;

			case CellType::CT_WOOD_FLOOR:
			case CellType::CT_KITCHEN_FLOOR:
			case CellType::CT_BATHROOM_FLOOR:
			case CellType::CT_CARPET_FLOOR:
			case CellType::CT_GRASS:
			case CellType::CT_PAVING_SLAB:

			case CellType::CT_DOOR_OPEN:

			case CellType::CT_K_COUNTER_DOOR:
			case CellType::CT_K_OVEN_DOOR:
			case CellType::CT_K_FRIDGE_DOOR:

			case CellType::CT_L_SHOWER:
			case CellType::CT_L_TOILET:
			case CellType::CT_L_SINK:
			case CellType::CT_L_BATH_UPPER:
			case CellType::CT_L_BATH_LOWER:

			case CellType::CT_B_BED_UPPER:
			case CellType::CT_B_BED_LOWER:

			case CellType::CT_B_WARDROBE_L_DOOR:
			case CellType::CT_B_WARDROBE_R_DOOR:
			
			case CellType::CT_UPSTAIR:
			case CellType::CT_DOWNSTAIR:
				return false;
				break;
			
			default:
				return false;
				break;
		}
	}
}
