#include "font.h"

Font::Font(const std::string& fontfile, size_t size) : m_font(fontfile.c_str()), m_size(size)
{
	m_font.FaceSize(m_size);
}

void Font::render(const std::string& msg, float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(1,-1,1);
	m_font.Render(msg.c_str());
	glPopMatrix();
}

Font::~Font()
{
}
