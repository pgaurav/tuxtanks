#ifndef AUDIO_H
#define AUDIO_H
#include <string>
#include <map>
#include <SDL/SDL_mixer.h>

class Audio
{
	public:
		int m_audiorate;
		unsigned int m_audioformat; 
		int m_audiochannels;
		int m_audiobuffers;
	protected:
		std::map<std::string, Mix_Music*> m_musics;
		std::map<std::string, Mix_Chunk*> m_chunks;
	public:
		Audio();
		void addMusic(const std::string& name, const std::string& file);
		void addSound(const std::string& name, const std::string& file);
		void removeMusic(const std::string& name);
		void removeSound(const std::string& name);
		int playSound(const std::string& name);
		void haltSound(int channel);
		void haltMusic();
		void playMusic(const std::string& name);
		virtual ~Audio();
};

#endif // AUDIO_H
