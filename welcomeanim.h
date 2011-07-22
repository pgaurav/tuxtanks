#ifndef WELCOMEANIM_H
#define WELCOMEANIM_H
#include "animation.h"
#include "texture.h"
#include "font.h"
#include "button.h"
#include "radio.h"
#include "gamedata.h"
#include "tank.h"

class WelcomeAnimation : public Animation
{
	protected:
		bool m_isMusicPlaying;
		TextureHash m_texhash;
		Font *m_bigfont;
		Font *m_smallfont;
		Button *m_btnExit;
		Button *m_btnNext;
		RadioButton *m_radio;
		Tank *m_tank1, *m_tank2;
		float m_ang1, m_ang2;
		float m_diff1, m_diff2;
	public:
		WelcomeAnimation(void *gamedata, Audio *audio, int w, int h);
		void render();
		int handleEvents(SDL_Event event);
		~WelcomeAnimation();
};

#endif // WELCOMEANIM_H
