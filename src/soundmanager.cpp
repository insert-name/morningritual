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
		
		//Set up sound
		this->sound_buffers[SoundType::NOTIFICATION].loadFromFile(this->data_directory + "/audio/sfx/SFX_notification_popup_010.ogg");
		
		//Set up music
		this->musics[MusicType::MAIN_GAMEPLAY].openFromFile(this->data_directory + "/audio/music/MUSIC_gameplay_danger_low_010.ogg");
		this->musics[MusicType::PANIC_1].openFromFile(this->data_directory + "/audio/music/MUSIC_gameplay_danger_medium_010.ogg");
		this->musics[MusicType::PANIC_2].openFromFile(this->data_directory + "/audio/music/MUSIC_gameplay_danger_high_010.ogg");
	}
	
	void SoundManager::playSound(SoundType type)
	{
		this->sounds[type].setBuffer(this->sound_buffers[type]);
		this->sounds[type].play();
		
		printf("Played sound\n");
	}
	
	void SoundManager::playMusic(MusicType type)
	{
		this->musics[type].play();
		
		printf("Playing music\n");
	}
}
