#include "widget.h"
#include "game.h"

namespace MorningRitual
{
	void Widget::tick()
	{
		this->lifetime --;
		
		if (this->lifetime < 60 && lifetime > 0)
		{
			this->alpha = (255 * lifetime) / 60;
			this->position.x -= (60 - lifetime) / 3;
		}
		else
			this->alpha = 255;
	}
	
	void Widget::click(Game* game)
	{
		if (this->notify_pos != glm::ivec3(-1, -1, -1))
		{
			game->moveTo(this->notify_pos);
		}
		
		if (this->lifetime > 60)
			this->lifetime = 60;
	}
}
