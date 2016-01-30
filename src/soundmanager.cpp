#include "soundmanager.h"

namespace MorningRitual
{
	SoundManager::SoundManager()
	{
		printf("Created sound manager\n");
	}
	
	void SoundManager::setup()
	{
		printf("Set up sound manager\n");
		
		this->sound_buffers[SoundType::NOTIFICATION].loadFromFile(this->data_directory + "/audio/sfx/SFX_notification_popup_010.ogg");
	}
	
	void SoundManager::play(SoundType type)
	{
		this->sounds[type].setBuffer(this->sound_buffers[type]);
		this->sounds[type].play();
		
		printf("Played sound\n");
	}
}
