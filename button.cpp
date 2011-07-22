#include "button.h"

Button::Button(const std::string& caption, const std::string& icon, int w, int h) : m_w(w), m_h(h), m_caption(caption)
{
	addTexture("icon", icon, m_texhash);
	m_enabled = true;
	m_clicked = false;
	m_hover = false;
	m_audio = NULL;
}

void Button::setAudio(Audio *audio)
{
	m_audio = audio;
}

void Button::render(int x, int y)
{
	m_x = x;
	m_y = y;
 	unsigned int tex = m_texhash["icon"];
	if(m_enabled == true)
	{
		if(m_hover == true)
		{
			glColor3f(1,1,0);
		}
		else
		{
			glColor3f(1,1,1);
		}
	}
	else 
	{
		glColor3f(0.2, 0.2, 0.2);
	}
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	glTexCoord2i(0,0);
	glVertex2f(m_x, m_y); 
	glTexCoord2i(1,0);
	glVertex2f(m_x+m_w, m_y);
	glTexCoord2i(1,1);
	glVertex2f(m_x+m_w, m_y+m_h); 
	glTexCoord2i(0,1);
	glVertex2f(m_x, m_y+m_h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

bool Button::isClicked()
{
	return m_clicked;
}

bool Button::isEnabled()
{
	return m_enabled;
}

void Button::setClicked(bool state)
{
	m_clicked = state;
}

void Button::setEnabled(bool state)
{
	m_enabled = state;
}

void Button::handleEvents(SDL_Event event)
{
	if(m_enabled == false)
	{
		return;
	}
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		int x = event.button.x;
		int y = event.button.y;
		if((x >= m_x && x <= m_x+m_w) && (y >= m_y && y <= m_y+m_h))
		{
			if(m_audio) m_audio->playSound("click");
			m_clicked = true;
		}
	}
	if(event.type == SDL_MOUSEMOTION)
	{
		int x = event.motion.x;
		int y = event.motion.y;
		if((x >= m_x && x <= m_x+m_w) && (y >= m_y && y <= m_y+m_h))
		{
			m_hover = true;
		}
		else
		{
			m_hover = false;
		}
	}
}

Button::~Button()
{
	deleteTextures(m_texhash);
}


