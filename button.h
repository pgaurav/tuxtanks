#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "texture.h"
#include "font.h"
#include "audio.h"

class Button
{
	protected:
		int m_w, m_h;
		int m_x, m_y;
		std::string m_caption;
		TextureHash m_texhash;
		bool m_enabled;
		bool m_clicked;
		bool m_hover;
		Audio *m_audio;
	public:
		Button(const std::string& caption, const std::string& icon, int w, int h);
		void setAudio(Audio *audio);
		void render(int x, int y);
		bool isClicked();
		bool isEnabled();
		void setClicked(bool state);
		void setEnabled(bool state);
		void handleEvents(SDL_Event event);
		virtual ~Button();
};

#endif // BUTTON_H
