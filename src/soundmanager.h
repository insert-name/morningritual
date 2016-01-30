#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "string"

#include "SFML/Audio.hpp"

namespace MorningRitual
{
	enum SoundType
	{
		NOTIFICATION = 0,
	};
	
	class SoundManager
	{
		public:
			std::string data_directory;
			
			sf::SoundBuffer sound_buffers[10];
			sf::Sound sounds[10];
			
			
			SoundManager();
			void setup();
			void play(SoundType type);
	};
}

#endif
