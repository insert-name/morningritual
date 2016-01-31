namespace MorningRitual
{
	enum CellGenericType
	{
		CGT_EMPTY,
		CGT_FLOOR,
		CGT_WALL,
		CGT_DOOR,
		CGT_FURNITURE,
		CGT_UPSTAIR,
		CGT_DOWNSTAIR,
	};
	
	enum CellType
	{
		CT_EMPTY	= ' ',
		CT_POND		= 'P',

		CT_WOOD_FLOOR		= '.',
		CT_KITCHEN_FLOOR	= ',',
		CT_BATHROOM_FLOOR	= ';',
		CT_CARPET_FLOOR		= ':',
		CT_GRASS			= '*',
		CT_PAVING_SLAB		= '"',

		CT_WALL_H,	= 'H'
		CT_WALL_V,	= 'V'
		CT_WALL_C,	= 'C'
		CT_WALL_T,	= 'T'
		CT_WALL_X,	= 'X'
		CT_WINDOW_SMALL,	= '|'
		CT_WINDOW_LARGE_L,	= '\'
		CT_WINDOW_LARGE_R,	= '/'
		
		CT_DOOR_OPEN,	= '+'
		CT_DOOR_CLOSED,	= '-'
		
		//Furniture
		CT_TABLE	= 't',
		CT_CHAIR	= 'c',

		CT_K_COUNTER_STRAIGHT	= '1',	
		CT_K_COUNTER_INNER		= '2',		
		CT_K_COUNTER_OUTER		= '3',		
		CT_K_COUNTER_DOOR		= '4',		
		CT_K_OVEN			= 'O',
		CT_K_OVEN_DOOR		= 'o',
		CT_K_FRIDGE			= 'F',
		CT_K_FRIDGE_DOOR	= 'f',
		CT_K_WCHINE			= 'W',
		CT_K_SINK			= 'S',

		CT_L_SHOWER		= 'p',
		CT_L_TOILET		= 'u',
		CT_L_SINK		= 's',
		CT_L_BATH_UPPER = 'B',
		CT_L_BATH_LOWER = 'b',

		CT_B_BED_UPPER	= '(',
		CT_B_BED_LOWER	= ')',
		CT_B_TABLE		= 'Y',
		CT_B_WARDROBE_L = '[',
		CT_B_WARDROBE_R = ']',
		CT_B_WARDROBE_L_DOOR = '9',
		CT_B_WARDROBE_R_DOOR = '0',

		CT_UPSTAIR		= '<',
		CT_DOWNSTAIR	= '>',
	};
	
	enum CellRotationMode 
	{
		CRM_NONE,
		CRM_CORNER,
		CRM_DOOR,
		CRM_HV,
		CRM_JUNCTION
		CRM_WALLSIDE,
	};

	struct Cell
	{
		public:
			int id;
			int data;

			CellRotationMode getRotationMode() 
			{
				switch (this->id) 
				{
					case CellType::CT_EMPTY:
					case CellType::CT_WOOD_FLOOR:
					case CellType::CT_KITCHEN_FLOOR:
					case CellType::CT_BATHROOM_FLOOR:
					case CellType::CT_CARPET_FLOOR:
					case CellType::CT_GRASS:
					case CellType::CT_PAVING_SLAB:
					return CellRotationMode::CRM_NONE;
						break;

					case CellType::CT_WALL_C:
					case CellType::CT_K_COUNTER_INNER:
					case CellType::CT_K_COUNTER_OUTER:
						return CellRotationMode::CRM_CORNER;
						break;

					case CellType::CT_DOOR_OPEN:
					case CellType::CT_DOOR_CLOSED:
						return CellRotationMode::CRM_DOOR;
						break;

					case CellType::CT_WALL_H:
					case CellType::CT_WALL_V:
					case CellType::CT_WINDOW_SMALL:
					case CellType::CT_WINDOW_LARGE_L:
					case CellType::CT_WINDOW_LARGE_R:
						return CellRotationMode::CRM_HV;
						break;

					case CellType::CT_WALL_T:
					case CellType::CT_WALL_X:
						return CellRotationMode::CRM_JUNCTION;
						break;

					case CellType::CT_K_COUNTER_STRAIGHT:
					case CellType::CT_K_OVEN:
					case CellType::CT_K_FRIDGE:
					case CellType::CT_K_SINK:
					case CellType::CT_L_SHOWER:
					case CellType::CT_L_TOILET:
					case CellType::CT_L_SINK:
					case CellType::CT_B_TABLE:
						return CellRotationMode::CRM_WALLSIDE;
						break; 

					default:
						return CellRotationMode::CRM_NONE;
						break;
				}
			}


			sf::Vector2u getTexCoords()
			{
				switch (this->id)
				{
				case CellType::CT_EMPTY:
					return sf::Vector2u(0, 0);
					break;

				case CellType::CT_WOOD_FLOOR:
					return sf::Vector2u(1, 0);
					break;

				case CellType::CT_KITCHEN_FLOOR:
					return sf::Vector2u(2, 0);
					break;

				case CellType::CT_BATHROOM_FLOOR:
					return sf::Vector2u(1, 1);
					break;

				case CellType::CT_CARPET_FLOOR:
					return sf::Vector2u(2, 1);
					break;

				case CellType::CT_WALL_H:
					return sf::Vector2u(3, 0);
					break;

				case CellType::CT_WALL_V:
					return sf::Vector2u(3, 1);
					break;

				case CellType::CT_WALL_C:
					return sf::Vector2u(4, 0);
					break;

				case CellType::CT_WALL_T:
					return sf::Vector2u(6, 0);
					break;

				case CellType::CT_WALL_X:
					return sf::Vector2u(8, 0);
					break;

				case CellType::CT_WINDOW_SMALL:
					return sf::Vector2u(9, 0);
					break;

				case CellType::CT_WINDOW_LARGE_L:
					return sf::Vector2u(10, 0);
					break;

				case CellType::CT_WINDOW_LARGE_R:
					return sf::Vector2u(10, 1);
					break;

				case CellType::CT_DOOR_OPEN:
					return sf::Vector2u(10, 2);
					break;

				case CellType::CT_DOOR_CLOSED:
					return sf::Vector2u(8, 2);
					break;

				case CellType::CT_K_COUNTER_STRAIGHT:
					return sf::Vector2u(0, 4);
					break; 

				case CellType::CT_K_COUNTER_INNER:
					return sf::Vector2u(4, 4);
					break;

				case CellType::CT_K_COUNTER_OUTER:
					return sf::Vector2u(2, 4);
					break;

				case CellType::CT_K_COUNTER_DOOR:
					return sf::Vector2u(0, 6);
					break;

				case CellType::CT_K_OVEN:
					return sf::Vector2u(8, 4);
					break;

				case CellType::CT_K_OVEN_DOOR:
					return sf::Vector2u(10, 4);
					break;

				case CellType::CT_K_WCHINE:
					return sf::Vector2u(6, 4);
					break;

				case CellType::CT_K_SINK:
					return sf::Vector2u(3, 1);
					break;

				case CellType::CT_L_SHOWER:
					return sf::Vector2u(6, 6);
					break;

				case CellType::CT_L_TOILET:
					return sf::Vector2u(8, 6);
					break;

				case CellType::CT_L_SINK:
					return sf::Vector2u(10, 6);
					break;

				case CellType::CT_L_BATH_UPPER:
					return sf::Vector2u(0, 8);
					break;

				case CellType::CT_L_BATH_LOWER:
					return sf::Vector2u(2, 8);
					break;

				case CellType::CT_B_BED_UPPER:
					return sf::Vector2u(4, 8);
					break;

				case CellType::CT_B_BED_LOWER:
					return sf::Vector2u(6, 8);
					break;

				case CellType::CT_B_TABLE:
					return sf::Vector2u(8, 8);
					break;

				case CellType::CT_B_WARDROBE_L:
					return sf::Vector2u(0, 10);
					break;

				case CellType::CT_B_WARDROBE_R:
					return sf::Vector2u(2, 10);
					break;

				case CellType::CT_B_WARDROBE_L_DOOR:
					return sf::Vector2u(4, 10);
					break;

				case CellType::CT_B_WARDROBE_R_DOOR:
					return sf::Vector2u(6, 10);
					break;

				default:
					return sf::Vector2u(0, 0);
					break;
				}
			}
			
			bool getSolid() 
			{
				switch (this->id)
				{
					case CellType::CT_EMPTY:
					case CellType::CT_POND:

					case CellType::CT_WALL_H:
					case CellType::CT_WALL_V:
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
						return false;
						break;
				}
			}

			CellGenericType getGenericType()
			{
				switch(this->id)
				{
					case CellType::CT_EMPTY:
					case CellType::CT_POND:
					return CellGenericType::CGT_EMPTY;
						break;
					
					case CellType::CT_WOOD_FLOOR:
					case CellType::CT_KITCHEN_FLOOR:
					case CellType::CT_BATHROOM_FLOOR:
					case CellType::CT_CARPET_FLOOR:
					case CellType::CT_GRASS:
					case CellType::CT_PAVING_SLAB:
					return CellGenericType::CGT_FLOOR;
						break;
					
					case CellType::CT_WALL_H:
					case CellType::CT_WALL_V:
					case CellType::CT_WALL_C:
					case CellType::CT_WALL_T:
					case CellType::CT_WALL_X:
					case CellType::CT_WINDOW_SMALL:
					case CellType::CT_WINDOW_LARGE_L:
					case CellType::CT_WINDOW_LARGE_R:
					return CellGenericType::CGT_WALL;
						break;

					case CellType::CT_DOOR_OPEN:
					case CellType::CT_DOOR_CLOSED:
					return CellGenericType::CGT_DOOR;
						break;

					case CellType::CT_K_COUNTER_STRAIGHT:
					case CellType::CT_K_COUNTER_INNER:
					case CellType::CT_K_COUNTER_OUTER:
					case CellType::CT_K_COUNTER_DOOR:
					case CellType::CT_K_OVEN:
					case CellType::CT_K_OVEN_DOOR:
					case CellType::CT_K_FRIDGE:
					case CellType::CT_K_FRIDGE_DOOR:
					case CellType::CT_K_WCHINE:
					case CellType::CT_K_SINK:
														
					case CellType::CT_L_SHOWER:
					case CellType::CT_L_TOILET:
					case CellType::CT_L_SINK:
					case CellType::CT_L_BATH_UPPER:
					case CellType::CT_L_BATH_LOWER:

					case CellType::CT_B_BED_UPPER:
					case CellType::CT_B_BED_LOWER:
					case CellType::CT_B_TABLE:
					case CellType::CT_B_WARDROBE_L:
					case CellType::CT_B_WARDROBE_R:
					case CellType::CT_B_WARDROBE_L_DOOR:
					case CellType::CT_B_WARDROBE_R_DOOR:
					return CellGenericType::CGT_FURNITURE;
						break;
				}
			}
	};
}
