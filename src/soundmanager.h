#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "string"

#include "SFML/Audio.hpp"

namespace MorningRitual
{
	class SoundManager
	{
		public:
			std::string data_directory;
			
			SoundManager();
			void setup();
	};
}

#endif
