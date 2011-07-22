#include "textbox.h"

TextBox::TextBox(const std::string& caption, int w = 200) : m_caption(caption), m_w(w), m_focussed(false), m_str("")
{
	m_h = 25;
	m_font = new Font("images/mono.ttf",18);
	m_enabled = true;
}

void TextBox::render(int x, int y)
{
	m_x = x;
	m_y = y + 25;
	glColor3f(0,1,0);
	m_font->render(m_caption, m_x, m_y - 25 + 17);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_x, m_y);glVertex2f(m_x + m_w, m_y);
	glVertex2f(m_x + m_w, m_y + m_h);glVertex2f(m_x, m_y + m_h);
	glEnd();
	std::string displayStr = m_str;
	if(m_focussed == true)
	{
		displayStr = displayStr + "|";
	}
	m_font->render(displayStr.c_str(), m_x + 4, m_y + 17);
}

bool TextBox::isFocussed()
{
	return m_focussed;
}

bool TextBox::isEnabled()
{
	return m_enabled;
}

void TextBox::setEnabled(bool state)
{
	m_enabled = state;
}

std::string TextBox::getText()
{
	return m_str;
}

void TextBox::setText(std::string& text)
{
	m_str = text;
}

void TextBox::handleEvents(SDL_Event event)
{
	if(m_enabled == false) return;
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		int x = event.button.x;
		int y = event.button.y;
		if((x >= m_x && x <= m_x + m_w) && (y >= m_y && y <= m_y + m_h))
		{
			m_focussed = true;
		} 
		else
		{
			m_focussed = false;
		}
	}
	if(event.type == SDL_KEYDOWN && m_focussed == true)
	{
		int key = event.key.keysym.sym;
		if((key >= 32 && key <= 126) && m_str.length() < 18)
		{
			m_str = m_str + char(key);
		}
		if((key == 8 || key == 127) && m_str.length() != 0)
		{
			m_str.erase(m_str.length() - 1, 1);
		}
	}
}

TextBox::~TextBox()
{
	delete m_font;
}
