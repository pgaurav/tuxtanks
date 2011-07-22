#ifndef INTROANIM_H
#define INTROANIM_H
#include <sstream>
#include "animation.h"
#include "texture.h"
#include "font.h"
#include "textbox.h"
#include "listbox.h"
#include "button.h"
#include "gamedata.h"
#include "radio.h"
#include "audio.h"

class IntroAnimation : public Animation
{
	protected:
		bool m_isMusicPlaying;
		TextureHash m_texhash;
		TextBox *m_textbox1;
		TextBox *m_textbox2;
		ListBox *m_listbox1;
		ListBox *m_listbox2;
		ListBox *m_listbox3;
		RadioButton *m_radiobtn;
		Button *m_btnRand;
		Button *m_btnExit;
		Button *m_btnNext;
		Button *m_btnleft;
		Button *m_btnright;
		Font *m_font;
		bool m_weaponsAlloted;
		int m_chooseturn;
	protected:
		void randomlyAllotWeapons();
		void allotWeapon(int chooseturn);
	public:
		IntroAnimation(void *gamedata, Audio *audio, int w, int h);
		void render();
		int handleEvents(SDL_Event event);
		~IntroAnimation();
};

#endif // INTROANIM_H
