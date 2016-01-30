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
		CT_EMPTY,
		CT_POND,

		CT_WOOD_FLOOR		= '.',
		CT_KITCHEN_FLOOR	= ',',
		CT_BATHROOM_FLOOR	= ';',
		CT_CARPET_FLOOR		= ':',
		CT_GRASS			= '*',
		CT_PAVING_SLAB		= '`',

		CT_WALL_H, = 'H'
		CT_WALL_V, = 'V'
		CT_WALL_C, = 'C'
		CT_WALL_T, = 'T'
		CT_WALL_X, = 'X'
		CT_WINDOW_SMALL, = '|'
		CT_WINDOW_LARGE_L, = '\'
		CT_WINDOW_LARGE_R, = '/'
		
		CT_DOOR_OPEN, = ''
		CT_DOOR_CLOSED, = ''
		
		//Furniture
		CT_TABLE,
		CT_CHAIR,

		CT_K_COUNTER_STRAIGHT,
		CT_K_COUNTER_INNER,
		CT_K_COUNTER_OUTER,
		CT_K_COUNTER_DOOR,
		CT_K_SINK,
		CT_K_OVEN,
		CT_K_OVEN_DOOR,
		CT_K_FRIDGE,
		CT_K_FRIDGE_DOOR,
		CT_K_WCHINE,

		CT_L_SHOWER,
		CT_L_TOILET,
		CT_L_SINK,
		CT_L_BATH_UPPER,
		CT_L_BATH_LOWER,

		CT_B_BED_UPPER,
		CT_B_BED_LOWER,
		CT_B_TABLE,
		CT_B_WARDROBE_L,
		CT_B_WARDROBE_R,
		CT_B_WARDROBE_L_DOOR,
		CT_B_WARDROBE_R_DOOR,

		CT_UPSTAIR,
		CT_DOWNSTAIR,
	}
	
	struct Cell
	{
		public:
			int id;
			int data;
			
			CellGenericType getGenericType()
			{
				switch(this->id)
				{
					case CellType::EMPTY:
					case CellType::POND:
					return CellGenericType::EMPTY;
						break;
					
					case CellType::WOOD_FLOOR:
					case CellType::KITCHEN_FLOOR:
					case CellType::BATHROOM_FLOOR;
					return CellGenericType::FLOOR;
						break;
					
					case CellType::WALL_H;
					return CellGenericType::WALL;
						break;

				}
			}
	};
}
