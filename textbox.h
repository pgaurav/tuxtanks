#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "font.h"
#include "audio.h"

class TextBox
{
	protected:
		int m_w, m_h;
		int m_x, m_y;
		bool m_focussed;
		bool m_enabled;
		std::string m_caption;
		std::string m_str;
		Font *m_font;
		Audio *m_audio;
	public:
		TextBox(const std::string& caption, int w);
		void addAudio(Audio *audio);
		void render(int x, int y);
		bool isFocussed();
		bool isEnabled();
		void setEnabled(bool state);
		std::string getText();
		void setText(std::string& text);
		void handleEvents(SDL_Event event);
		virtual ~TextBox();
};

#endif // TEXTBOX_H
