#include "audio.h"


Audio::Audio()
{
	int m_audiorate = 22050;
	unsigned int m_audioformat = AUDIO_S16; 
	int m_audiochannels = 2;
	int m_audiobuffers = 4096;
	Mix_OpenAudio(m_audiorate,m_audioformat,m_audiochannels,m_audiobuffers);
}

void Audio::addMusic(const std::string& name, const std::string& file)
{
	m_musics[name] = Mix_LoadMUS(file.c_str());
}

void Audio::addSound(const std::string& name, const std::string& file)
{
	m_chunks[name] = Mix_LoadWAV(file.c_str());
}

void Audio::removeMusic(const std::string& name)
{
	Mix_HaltMusic();
	Mix_FreeMusic(m_musics[name]);
	m_musics.erase(name);
}

void Audio::removeSound(const std::string& name)
{
	Mix_FreeChunk(m_chunks[name]);
	m_chunks.erase(name);
}

int Audio::playSound(const std::string& name)
{
	int channel = Mix_PlayChannel(-1, m_chunks[name], 0);
	while(Mix_Playing(channel) != 0);
	return channel;
}

void Audio::haltSound(int channel)
{
	Mix_HaltChannel(channel);
}

void Audio::haltMusic()
{
	Mix_HaltMusic();
}

void Audio::playMusic(const std::string& name)
{
	Mix_PlayMusic(m_musics[name], 0);
}

Audio::~Audio()
{
	Mix_HaltMusic();
	std::map<std::string, Mix_Music*>::iterator iterm;
	for(iterm = m_musics.begin(); iterm != m_musics.end(); ++iterm)
	{
		Mix_FreeMusic(iterm->second);
	}
	std::map<std::string, Mix_Chunk*>::iterator iters;
	for(iters = m_chunks.begin(); iters != m_chunks.end(); ++iters)
	{
		Mix_FreeChunk(iters->second);
	}
	Mix_CloseAudio();
}

