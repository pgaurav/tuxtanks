#include "texture.h"

void addTexture(const std::string& id, const std::string& img, TextureHash& texhash)
{
	unsigned int tex;
	GLenum texture_format;
	int  nOfColors;
	int width, height;
	SDL_Surface *imgsurface = SDL_LoadBMP(img.c_str());
	if ( (imgsurface->w & (imgsurface->w - 1)) != 0 ) {
		std::cerr << "warning: image.bmp's width is not a power of 2" << std::endl;
	}
	if ( (imgsurface->h & (imgsurface->h - 1)) != 0 ) {
		std::cerr << "warning: image.bmp's height is not a power of 2" << std::endl;
	}
	nOfColors = imgsurface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (imgsurface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (imgsurface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
		std::cerr << "warning: image loading may break" << std::endl;
	}
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, imgsurface->w, imgsurface->h, 0,
		     texture_format, GL_UNSIGNED_BYTE, imgsurface->pixels );
	texhash[id] = tex;
	SDL_FreeSurface(imgsurface);
}

void deleteTexture(const std::string& id, TextureHash& texhash)
{
	unsigned int tex = texhash[id];
	glDeleteTextures(1, &tex);
	texhash.erase(id);
}

void deleteTextures(TextureHash& texhash)
{
	TextureHashIter iter;
	for(iter = texhash.begin(); iter != texhash.end(); ++iter)
	{
		unsigned int tex = iter->second;
		glDeleteTextures(1, &tex);
	}
}
