#include "introanim.h"

IntroAnimation::IntroAnimation(void *gamedata, Audio *audio, int w, int h) : Animation(gamedata, audio, w, h)
{
	m_isMusicPlaying = false;
	addTexture("background","images/welcome.bmp", m_texhash);
	m_font = new Font("images/mono.ttf", 18);
	m_textbox1 = new TextBox("Player1's name", 200);
	m_textbox1->addAudio(audio);
	m_textbox2 = new TextBox("Player2's name", 200);
	m_textbox2->addAudio(m_audio);
	m_listbox1 = new ListBox("Player1's weapons", 200, 250);
	m_listbox2 = new ListBox("Available weapons", 200, 500);
	m_listbox2->addAudio(m_audio);
	m_listbox3 = new ListBox("Player2's weapons", 200, 250);
	m_radiobtn = new RadioButton("Selection mode", 200);
	m_radiobtn->addItem("Random selection");
	m_radiobtn->addItem("Manual selection");
	m_radiobtn->addAudio(m_audio);
	// start - just for testing
	for(int i=0; i<10; ++i)
	{
		std::stringstream ss;
		ss << i+1;
		std::string bullet = "bullet" + ss.str();
		m_listbox2->addItem(bullet,"images/bullet.bmp");
		m_listbox2->addItem(bullet,"images/bullet.bmp");
	}
	// end - just for testing
	m_btnRand = new Button("","images/btnshuffle.bmp", 50, 50);
	m_btnExit = new Button("", "images/exit.bmp", 50, 50);
	m_btnNext = new Button("", "images/next.bmp", 50, 50);
	m_btnleft = new Button("", "images/left.bmp", 50, 50);
	m_btnright = new Button("", "images/right.bmp", 50, 50);
	m_btnRand->setEnabled(true);
	m_btnNext->setEnabled(false);
	m_btnright->setEnabled(false);
	m_btnleft->setEnabled(false);
	m_weaponsAlloted = false;
	m_chooseturn = 0;
}

void IntroAnimation::render()
{
	if(m_isAnimating == true)
	{
		randomlyAllotWeapons();
	}
	if(m_isMusicPlaying == false)
	{
		m_audio->playMusic("background");
		m_isMusicPlaying = true;
	}
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texhash["background"]);
	glBegin(GL_QUADS);
	glTexCoord2i(0,0);
	glVertex2f(0,0); 
	glTexCoord2i(1,0);
	glVertex2f(m_w, 0);
	glTexCoord2i(1,1);
	glVertex2f(m_w, m_h); 
	glTexCoord2i(0,1);
	glVertex2f(0, m_h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	m_btnRand->render(50, m_h - 70);
	m_btnRand->setAudio(m_audio);
	m_btnNext->render(m_w-70, m_h-70);
	m_btnNext->setAudio(m_audio);
	m_btnExit->render(m_w-140, m_h-70);
	m_btnExit->setAudio(m_audio);
	m_btnleft->render(250, 225);
	m_btnleft->setAudio(m_audio);
	m_btnright->render(500, 225);
	m_btnright->setAudio(m_audio);
	m_textbox1->render(50, 25);
	m_textbox2->render(m_w - 250, 25);
	m_listbox1->render(50, 100);
	m_listbox2->render(m_w/2 - 100, 25);
	m_listbox3->render(m_w - 250, 100);
	m_radiobtn->render(50, m_h - 175);
	glColor3f(0,1,0);
	m_font->render("1. Enter names above", m_w-250, m_h - 150);
	m_font->render("2. Click next button", m_w-250, m_h - 125);
}

int IntroAnimation::handleEvents(SDL_Event event)
{
	if(m_isAnimating == true)
	{
		return ANIMATION_EVENT_NONE;
	}
	m_textbox1->handleEvents(event);
	m_textbox2->handleEvents(event);
	m_listbox2->handleEvents(event);
	m_radiobtn->handleEvents(event);
	if(m_weaponsAlloted == false && m_radiobtn->isEnabled() && m_btnRand->isClicked() == false)
	{
		if(m_radiobtn->getChecked() == "Random selection")
		{
			m_btnRand->setEnabled(true);
			m_listbox2->setEnabled(false);
			m_btnleft->setEnabled(false);
			m_btnright->setEnabled(false);
		}
		else
		{
			m_btnRand->setEnabled(false);
			m_listbox2->setEnabled(true);
			m_btnleft->setEnabled(true);
		}
	}
	if(m_textbox1->getText().length() != 0 && m_textbox2->getText().length() != 0) 
	{
		if(m_weaponsAlloted == true)
		{
			m_btnNext->setEnabled(true);
		}
	}
	else
	{
		m_btnNext->setEnabled(false);
	}
	m_btnRand->handleEvents(event);
	m_btnExit->handleEvents(event);
	m_btnNext->handleEvents(event);
	m_btnright->handleEvents(event);
	m_btnleft->handleEvents(event);
	if(m_btnright->isClicked())
	{
		m_chooseturn = !m_chooseturn;
		m_btnright->setEnabled(false);
		m_btnright->setClicked(false);
		m_btnleft->setEnabled(true);
		allotWeapon(1);
	}
	if(m_btnleft->isClicked())
	{
		m_radiobtn->setEnabled(false);
		m_chooseturn = !m_chooseturn;
		m_btnleft->setEnabled(false);
		m_btnleft->setClicked(false);
		m_btnright->setEnabled(true);
		allotWeapon(0);
	}
	if(m_btnRand->isEnabled() && m_btnRand->isClicked())
	{
		m_isAnimating = true;
		if(m_textbox1->getText().length() != 0 && m_textbox2->getText().length() != 0) 
		{
			m_btnNext->setEnabled(true);
		}
		if(m_listbox2->getItemArr().size() == 0) 
		{
			m_btnRand->setEnabled(false);
		}
	}
	if(m_btnExit->isClicked())
	{
		return ANIMATION_EVENT_EXIT;
	}
	if(m_btnNext->isClicked())
	{
		m_audio->haltMusic();
		return ANIMATION_EVENT_NEXT;
	}
	return ANIMATION_EVENT_NONE;
}

void IntroAnimation::allotWeapon(int chooseturn)
{
	if(chooseturn == 0)
	{
		std::string weaponName = m_listbox2->getChecked();
		int texid = m_listbox2->getTextureHash()[weaponName];
		m_listbox1->addItem(weaponName, texid);
		m_listbox2->removeItem(weaponName);
	}
	else
	{
		std::string weaponName = m_listbox2->getChecked();
		int texid = m_listbox2->getTextureHash()[weaponName];
		m_listbox3->addItem(weaponName, texid);
		m_listbox2->removeItem(weaponName);
	}
	if(m_listbox2->getItemArr().size() == 0)
	{
		m_weaponsAlloted = true;
		m_btnleft->setEnabled(false);
		m_btnright->setEnabled(false);
	}
}

void IntroAnimation::randomlyAllotWeapons()
{
	static int turn = 0;
	srand(SDL_GetTicks());
	if(m_listbox2->getItemArr().size() != 0)
	{
		m_audio->playSound("click");
		m_isAnimating = true;
		int idx = rand() % m_listbox2->getItemArr().size();
		if(turn == 0)
		{
			std::string item = m_listbox2->getItemArr()[idx];
			m_listbox1->addItem(item, m_listbox2->getTextureHash()[item]);
			turn = !turn;
		}
		else
		{
			std::string item = m_listbox2->getItemArr()[idx];
			m_listbox3->addItem(item, m_listbox2->getTextureHash()[item]);
			turn = !turn;
		}
		m_listbox2->getItemArr().erase(m_listbox2->getItemArr().begin() + idx);
	}
	else
	{
		m_isAnimating = false;
	}
	m_weaponsAlloted = true;
	m_radiobtn->setEnabled(false);
	m_listbox2->setEnabled(false);
}

IntroAnimation::~IntroAnimation()
{
	deleteTextures(m_texhash);
	delete m_font;
	delete m_textbox1;
	delete m_textbox2;
	delete m_listbox1;
	delete m_listbox2;
	delete m_listbox3;
	delete m_btnRand;
	delete m_btnExit;
	delete m_btnNext;
	delete m_radiobtn;
}

