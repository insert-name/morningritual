namespace MorningRitual
{
	enum CellType
	{
		EMPTY,
		FLOOR,
		WALL,
		FURNITURE,
		DOOR,
		UPSTAIR,
		DOWNSTAIR,
	};
	
	struct Cell
	{
		public:
			CellType type;
			int variant;
			bool solid;
			int state;	
	};
}
