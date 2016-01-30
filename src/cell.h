#ifndef CELL_H
#define CELL_H

namespace MorningRitual
{
	class World;
	
	enum CellType
	{
		CT_EMPTY = 0,
		CT_FLOOR = 1,
		CT_WALL = 2,
		CT_FURNITURE = 3,
		CT_DOOR = 4,
		CT_UPSTAIR = 5,
		CT_DOWNSTAIR = 6,
	};
	
	enum CellVariant
	{
		CV_EMPTY = 0,
		
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
				this->type = CellType::CT_EMPTY;
				this->variant = 0;
				this->solid = true;
				this->state = 0;
			}
			
			Cell(CellType type, int variant, bool solid, int state)
			{
				this->type = type;
				this->variant = variant;
				this->solid = solid;
				this->state = state;
			}
			
			bool isSolid();
			
			void click(World* world);
	};
}

#endif
