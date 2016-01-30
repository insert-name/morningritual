#ifndef GUI_H
#define GUI_H

#include "glm/glm.hpp"

#include "widget.h"

namespace MorningRitual
{
	class GUI
	{
		public:
			std::vector<Widget> notification_widgets;
			
			std::string data_directory;
			
			GUI();
			void setup();
			void tick();
			void notify(std::string msg, glm::ivec3 position = glm::ivec3(-1, -1, -1));
	};
}

#endif
