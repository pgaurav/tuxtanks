#include "tank.h"

Tank::Tank(int w, int h)
{
	m_w = w;
	m_h = h;
	m_r = 0; m_g = 0; m_b = 0;
	addTexture("tbase", "images/tbase.bmp", m_texhash);
	addTexture("tpipe", "images/tpipe.bmp", m_texhash);
}

void Tank::setColor(float r, float g, float b)
{
	m_r = r; m_g = g; m_b = b;
}

void Tank::setAngle(float angle)
{
	m_angle = angle;
}

float Tank::getAngle()
{
	return m_angle;
}

void Tank::render(int x, int y)
{
	m_x = x;
	m_y = y;
	glColor3f(m_r, m_g, m_b);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(m_x+m_w/2.0, m_y+2.0*m_h/10.0, 0);
	glRotatef(m_angle, 0, 0, 1);
	glTranslatef(-m_x-m_w/2.0, -m_y-2.0*m_h/10.0, 0);
	glBindTexture(GL_TEXTURE_2D, m_texhash["tpipe"]);
	glBegin(GL_QUADS);
	glTexCoord2i(0,0);
	glVertex2f(m_x+m_w/2.0, m_y+m_h/10.0);
	glTexCoord2i(1,0);
	glVertex2f(m_x+m_w, m_y+m_h/10.0);
	glTexCoord2i(1,1);
	glVertex2f(m_x+m_w, m_y+3.0*m_h/10.0);
	glTexCoord2i(0,1);
	glVertex2f(m_x+m_w/2.0, m_y+3.0*m_h/10.0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, m_texhash["tbase"]);
	glBegin(GL_QUADS);
	glTexCoord2i(0,0);
	glVertex2f(m_x, m_y);
	glTexCoord2i(1,0);
	glVertex2f(m_x + m_w, m_y);
	glTexCoord2i(1,1);
	glVertex2f(m_x + m_w, m_y + m_h);
	glTexCoord2i(0,1);
	glVertex2f(m_x, m_y + m_h);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

Tank::~Tank()
{
	deleteTextures(m_texhash);
}
