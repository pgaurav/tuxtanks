#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL/SDL.h>
#include "audio.h"

const int ANIMATION_EVENT_NONE = 0;
const int ANIMATION_EVENT_EXIT = 1;
const int ANIMATION_EVENT_PREV = 2;
const int ANIMATION_EVENT_NEXT = 3;

class Animation
{
	protected:
		int m_w, m_h;
		void *m_gamedata;
		Audio *m_audio;
		bool m_isAnimating;
	public:
		Animation(void *gamedata, Audio *audio, int w, int h) : m_gamedata(gamedata), m_audio(audio), m_w(w), m_h(h), m_isAnimating(false){}
		virtual void render() = 0;
		virtual int handleEvents(SDL_Event event) = 0;
		virtual ~Animation(){}
};

#endif // ANIMATION_H
