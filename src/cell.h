#ifndef CELL_H
#define CELL_H

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
			
			Cell()
			{
				this->type = CellType::EMPTY;
				this->variant = 0;
				this->solid = false;
				this->state = 0;
			}
			
			Cell(CellType type, int variant, bool solid, int state)
			{
				this->type = type;
				this->variant = variant;
				this->solid = solid;
				this->state = state;
			}
	};
}

#endif
