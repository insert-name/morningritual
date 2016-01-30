namespace MorningRitual
{
	enum CellGenericType
	{
		EMPTY,
		FLOOR,
		WALL,
		DOOR,
		FURNITURE,
		UPSTAIR,
		DOWNSTAIR,
	};
	
	enum CellType
	{
		EMPTY,
		POND,
		
		WOOD_FLOOR,
		KITCHEN_FLOOR,
		BATHROOM_FLOOR,
		CARPET_FLOOR,
		GRASS,
		PAVING_SLAB,
		
		
		
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
					return CellGenericType::FLOOR;
						break;
					
				}
			}
	};
}
