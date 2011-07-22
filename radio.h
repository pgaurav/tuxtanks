#ifndef RADIO_H
#define RADIO_H
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "font.h"
#include "audio.h"

class RadioButton
{
	protected:
		int m_x, m_y;
		int m_w, m_h;
		std::string m_caption;
		std::vector<std::string> m_items;
		int m_curitem;
		int m_curhoveritem;
		Font *m_font;
		bool m_enabled;
		Audio *m_audio;
	public:
		RadioButton(const std::string& caption, int w = 200);
		void addAudio(Audio *audio);
		void render(int x, int y);
		void addItem(const std::string& item); 
		void setChecked(const std::string& item);
		std::string getChecked();
		void handleEvents(SDL_Event event);
		bool isEnabled();
		void setEnabled(bool truth);
		virtual ~RadioButton();
};

#endif // RADIO_H
