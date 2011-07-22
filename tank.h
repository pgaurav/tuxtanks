#ifndef TANK_H
#define TANK_H
#include "texture.h"

class Tank
{
	private:
		float m_w, m_h;
		float m_x, m_y;
		float m_angle;
		float m_r, m_g, m_b;
		TextureHash m_texhash;
	public:
		Tank(int w, int h);
		void setColor(float r, float g, float b);
		void setAngle(float angle);
		float getAngle();
		void render(int x, int y);
		virtual ~Tank();

};

#endif // TANK_H
