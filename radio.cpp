#include "radio.h"

RadioButton::RadioButton(const std::string& caption, int w)
{
	m_x = 0; m_y = 0; m_w = w; m_h = 0;
	m_caption = caption;
	m_curitem = 0;
	m_curhoveritem = -1;
	m_font = new Font("images/mono.ttf",18);
	m_enabled = true;
	m_audio = NULL;
}

void RadioButton::addAudio(Audio *audio)
{
	m_audio = audio;
}

void RadioButton::render(int x, int y)
{
	m_x = x; m_y = y + 25;
	glColor3f(0,1,0);
	m_font->render(m_caption, m_x, m_y - 25 + 17);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_x, m_y);
	glVertex2f(m_x + m_w, m_y);
	glVertex2f(m_x + m_w, m_y + m_h);
	glVertex2f(m_x, m_y + m_h);
	glEnd();
	for(int i=0; i < m_items.size(); ++i)
	{
		int x = m_x + 4;
		int y = m_y + i*25 + 17;
		if(i == m_curitem)
		{
			glColor3f(1, 0, 0);
			m_font->render(" " + m_items[i], x, y);
		}
		else if(i == m_curhoveritem)
		{
			glColor3f(1, 1, 0);
			m_font->render(" " + m_items[i], x, y);
		}
		else
		{
			glColor3f(0, 1, 0);
			m_font->render(" " + m_items[i], x, y);
		}
	}
}

void RadioButton::addItem(const std::string& item)
{
	m_items.push_back(item);
	m_h += 25;
}

void RadioButton::setChecked(const std::string& item)
{
	int i=0;
	for(i=0; i<m_items.size(); ++i)
	{
		if(m_items[i] == item) break;
	}
	if(i < m_items.size())
	{
		m_curitem = i;
	}
}

std::string RadioButton::getChecked()
{
	return m_items[m_curitem];
}

void RadioButton::handleEvents(SDL_Event event)
{
	if(m_enabled == false) return;
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		int x = event.button.x;
		int y = event.button.y;	
		if((x >= m_x && x <= m_x+m_w) && (y >= m_y && y <= m_y+m_h))
		{
			if(m_audio) m_audio->playSound("click");
			m_curitem = (y - m_y)/25;
		}
	}
	if(event.type == SDL_MOUSEMOTION)
	{
		int x = event.motion.x;
		int y = event.motion.y;	
		if((x >= m_x && x <= m_x+m_w) && (y >= m_y && y <= m_y+m_h))
		{
			m_curhoveritem = (y - m_y)/25;
		}
		else
		{
			m_curhoveritem = -1;
		}
	}
}

bool RadioButton::isEnabled()
{
	return m_enabled;
}

void RadioButton::setEnabled(bool truth)
{
	m_enabled = truth;
}

RadioButton::~RadioButton()
{
	delete m_font;
}

