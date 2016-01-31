#ifndef CELL_H
#define CELL_H

#include "SFML/Graphics.hpp"

namespace MorningRitual
{
	class World;
	
	/*enum CellType
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
	};*/
}

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

		CT_WALL_H	= 'H',
		CT_WALL_V	= 'V',
		CT_WALL_C	= 'C',
		CT_WALL_T	= 'T',
		CT_WALL_X	= 'X',
		CT_WINDOW_SMALL	= '|',
		CT_WINDOW_LARGE_L	= '\\',
		CT_WINDOW_LARGE_R	= '/',
		
		CT_DOOR_OPEN	= '+',
		CT_DOOR_CLOSED	= '-',
		
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
	
	struct Cell
	{
		public:
			int id;
			int data;
			
			Cell()
			{
				this->id = CellType::CT_EMPTY;
				this->data = 0;
			}
			
			Cell(CellType type, int data)
			{
				this->id = type;
				this->data = data;
			}
			
			void click(World* world);
			
			bool getSolid();
			
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

				default:
					return sf::Vector2u(0, 0);
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
					case CT_B_TABLE:
					case CT_B_WARDROBE_L:
					case CT_B_WARDROBE_R:
					case CT_B_WARDROBE_L_DOOR:
					case CT_B_WARDROBE_R_DOOR:
					return CellGenericType::CGT_FURNITURE;
						break;
				}
			}
	};
}

#endif
