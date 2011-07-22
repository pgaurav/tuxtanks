#include "welcomeanim.h"

WelcomeAnimation::WelcomeAnimation(void *gamedata, Audio *audio, int w, int h) : Animation(gamedata, audio, w, h)
{
	m_isMusicPlaying = false;
	m_ang1 = 0; m_ang2 = 0;
	m_diff1 = -1; m_diff2 = -1;
	m_tank1 = new Tank(100,50);
	m_tank2 = new Tank(100,50);
	m_tank1->setAngle(m_ang1);
	m_tank2->setAngle(m_ang2);
	m_tank1->setColor(0,1,0);
	m_tank2->setColor(1,0,0);
	addTexture("background","images/welcome.bmp", m_texhash);
	m_btnExit = new Button("", "images/exit.bmp", 50, 50);
	m_btnNext = new Button("", "images/next.bmp", 50, 50); 
	m_radio = new RadioButton("Choose a game mode", 200);
	m_radio->addItem("One player");
	m_radio->addItem("Two player");
	m_radio->setChecked("Two player");
	m_bigfont = new Font("images/mono.ttf", 24);
	m_smallfont = new Font("images/mono.ttf", 18);
	m_audio->addMusic("welcomebackground", "audio/background.wav");
}

void WelcomeAnimation::render()
{
	if(m_isMusicPlaying == false)
	{
		m_audio->playMusic("welcomebackground");
		m_isMusicPlaying = true;
	}
	m_ang1 = m_ang1 + m_diff1;
	m_ang2 = m_ang2 + m_diff2;
	if(m_ang1 == -40) m_diff1 = 0;
	if(m_ang1 == 0) m_diff1 = -0.5;
	if(m_ang2 == -40) m_diff2 = 0;
	if(m_ang2 == 0) m_diff2 = -0.5;
	m_tank1->setAngle(m_ang1);
	m_tank2->setAngle(m_ang2);
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
	m_tank1->render(100, 275);
	glPushMatrix();
	glTranslatef(m_w-100, 275, 0);
	glScalef(-1,1,1);
	glTranslatef(-m_w+100, -275, 0);
	m_tank2->render(m_w-100, 275);
	glPopMatrix();
	glColor3f(0,1,0);
	m_bigfont->render("Welcome to Tuxtanks - A battle game of tanks!", 80, 40);
	m_smallfont->render("A free game created by Vyom (vyom@gatech.edu)", 150, 70);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_btnNext->render(m_w-70, m_h-70);
	m_btnExit->render(m_w-140, m_h-70);
	glDisable(GL_BLEND);
	m_radio->render(m_w/2 - 100, m_h/2 - 50);
}

int WelcomeAnimation::handleEvents(SDL_Event event)
{
	m_btnNext->handleEvents(event);
	m_btnExit->handleEvents(event);
	m_radio->handleEvents(event);
	if(m_btnNext->isClicked())
	{
		m_audio->haltMusic();
		return ANIMATION_EVENT_NEXT;
	}
	if(m_btnExit->isClicked())
	{
		return ANIMATION_EVENT_EXIT;
	}
	return ANIMATION_EVENT_NONE;
}

WelcomeAnimation::~WelcomeAnimation()
{
	deleteTextures(m_texhash);
	delete m_bigfont;
	delete m_smallfont;
	delete m_btnExit;
	delete m_btnNext;
	delete m_radio;
	delete m_tank1;
	delete m_tank2;
}

