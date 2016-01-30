#include "stdio.h"

#include "gui.h"

namespace MorningRitual
{
	GUI::GUI()
	{
		printf("Created GUI\n");
	}
	
	void GUI::setup()
	{
		this->widgets.push_back(Widget());
		this->widgets.back().texture.loadFromFile(this->data_directory + "/GUI/notification.png");
	}
}
