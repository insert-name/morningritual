#ifndef GUI_H
#define GUI_H

#include "widget.h"

namespace MorningRitual
{
	class GUI
	{
		public:
			std::vector<Widget> widgets;
			
			std::string data_directory;
			
			GUI();
			void setup();
	};
}

#endif
