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
		this->notify("Testing messages once");
		this->notify("Testing 2");
		this->notify("Test 3");
		
		this->permanent.push_back(Widget());
		this->permanent.back().decay = false;
		this->permanent.back().texture.loadFromFile(this->data_directory + "/GUI/29 clock.png");
		this->permanent.back().position = sf::Vector2f(350.0f, 0.0f);
		
		//Setup sound manager
		this->sound_manager.data_directory = this->data_directory;
		this->sound_manager.setup();
		this->sound_manager.playMusic(MusicType::MAIN_GAMEPLAY);
		//this->sound_manager.playMusic(MusicType::PANIC_1);
		//this->sound_manager.playMusic(MusicType::PANIC_2);
	}
	
	void GUI::tick()
	{
		for (int i = 0; i < this->notification_widgets.size(); i ++)
		{
			this->notification_widgets[i].tick();
		}
		
		int i = 0;
		while (i < this->notification_widgets.size())
		{
			if (this->notification_widgets[i].lifetime <= 0)
			{
				printf("Deleted notification widget\n");
				this->notification_widgets[i] = this->notification_widgets.back();
				this->notification_widgets.pop_back();
			}
			else
				i++;
		}
	}
	
	void GUI::notify(std::string msg, glm::ivec3 position)
	{
		this->notification_widgets.push_back(Widget());
		this->notification_widgets.back().lifetime = 300;
		this->notification_widgets.back().message = msg;
		this->notification_widgets.back().position = sf::Vector2f(16, 560);
		this->notification_widgets.back().notify_pos = position;
		this->notification_widgets.back().texture.loadFromFile(this->data_directory + "/GUI/notification.png");
		
		for (int i = 0; i < this->notification_widgets.size(); i ++)
			this->notification_widgets[i].position.y -= 80;
		
			this->sound_manager.playSound(SoundType::NOTIFICATION);
	}
}
