#ifndef FONT_H
#define FONT_H
#include <string>
#include <SDL/SDL_opengl.h>
#include <FTGL/ftgl.h>

class Font
{
	protected:
		size_t m_size;
		FTGLPolygonFont m_font;
	public:
		Font(const std::string& fontfile, size_t size = 24);
		void render(const std::string& msg, float x, float y, float z=0);
		virtual ~Font();
};

#endif // FONT_H


