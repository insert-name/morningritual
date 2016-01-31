#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "string"

#include "SFML/Audio.hpp"

namespace MorningRitual
{
	enum SoundType
	{
		NOTIFICATION = 0,
		DOOR_CLOSE = 1,
		DOOR_OPEN = 2,
	};
	
	enum MusicType
	{
		MAIN_GAMEPLAY,
		PANIC_1,
		PANIC_2,
	};
	
	class SoundManager
	{
		public:
			std::string data_directory;
			
			sf::SoundBuffer sound_buffers[10];
			sf::Sound sounds[10];
			
			sf::Music musics[10];
			
			bool sound_muted = false;
			bool back_muted = false;
			
			
			SoundManager();
			void setup();
			void update();
			void playSound(SoundType type);
			void playMusic(MusicType type);
	};
}

#endif
