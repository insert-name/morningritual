#include "widget.h"
#include "game.h"

namespace MorningRitual
{
	void Widget::tick()
	{
		this->lifetime --;
		
		if (this->startlife < 0)
			this->startlife = this->lifetime;
		
		if (this->lifetime < 60 && lifetime > 0)
		{
			this->alpha = (255 * lifetime) / 60;
			this->position.x -= (60 - lifetime) / 3;
		}
		else
			this->alpha = 255;
		
		if (this->lifetime > this->startlife - 60)
			this->alpha = (255 * (this->startlife - this->lifetime)) / 60;
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
