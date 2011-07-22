#include "listbox.h"

ListBox::ListBox(const std::string& caption, int w, int h) : m_caption(caption), m_w(w), m_h(h)
{
	m_curitem = -1;
	m_hoveritem = -1;
	m_font = new Font("images/mono.ttf", 18);
	m_enabled = true;
	m_audio = NULL;
}

void ListBox::addAudio(Audio *audio)
{
	m_audio = audio;
}

void ListBox::render(int x, int y)
{
	m_x = x; m_y = y + 25;
	glColor3f(0,1,0);
	m_font->render(m_caption.c_str(), m_x, m_y - 25 + 17);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_x, m_y); glVertex2f(m_x + m_w, m_y);
	glVertex2f(m_x + m_w, m_y + m_h); glVertex2f(m_x, m_y + m_h);
	glEnd();
	for(int i=0; i < m_items.size(); ++i)
	{
		int x = m_x + 4;
		int y = m_y + i*25 + 17;
		if(i == m_curitem)
		{
			glColor3f(1, 0, 0);
			m_font->render(" " + m_items[i], x + 30, y);
		}
		else if(i == m_hoveritem)
		{
			glColor3f(1, 1, 0);
			m_font->render(" " + m_items[i], x + 30, y);
		}
		else
		{
			glColor3f(0, 1, 0);
			m_font->render(" " + m_items[i], x + 30, y);
		}
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		int tex = m_icons[m_items[i]];
	  	glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
		glTexCoord2i(0,0);
		glVertex2f(x, m_y + i*25);
		glTexCoord2i(1,0);
		glVertex2f(x + 25, m_y + i*25);
		glTexCoord2i(1,1);
		glVertex2f(x + 25, m_y + (i+1)*25);
		glTexCoord2i(0,1);
		glVertex2f(x, m_y + (i+1)*25);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glColor3f(0,1,0);
	}
}

void ListBox::addItem(const std::string& item, const std::string& icon)
{
	m_items.push_back(item);
	addTexture(item, icon, m_icons);
}

void ListBox::addItem(const std::string& item, int textureid)
{
	m_items.push_back(item);
	m_icons[item] = textureid;
}

void ListBox::removeItem(const std::string& item)
{
	int i=0;
	for(i=0; i<m_items.size(); ++i)
	{
		if(m_items[i] == item) break;
	}
	if(i < m_items.size()) 
	{
		m_items.erase(m_items.begin() + i);
	}
	if(m_enabled == true)
	{
		if(m_items.size() - 1 <= i)
		{
			m_curitem = m_items.size() - 1;
		}
		else
		{
			m_curitem = i;
		}
	}
}

void ListBox::setChecked(const std::string& item)
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

std::string ListBox::getChecked()
{
	return m_items[m_curitem];
}

std::vector<std::string>& ListBox::getItemArr()
{
	return m_items;
}

TextureHash ListBox::getTextureHash()
{
	return m_icons;
}

void ListBox::handleEvents(SDL_Event event)
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
			m_hoveritem = (y - m_y)/25;
		}
		else
		{
			m_hoveritem = -1;
		}
	}
}

bool ListBox::isEnabled()
{
	return m_enabled;
}

void ListBox::setEnabled(bool truth)
{
	m_enabled = truth;
	if(m_enabled == false)
	{
		m_curitem = -1;
	}
	else
	{
		if(m_curitem == -1)
		{
			m_curitem = 0;
		}
	}
}

ListBox::~ListBox()
{
	deleteTextures(m_icons);
	delete m_font;
}
