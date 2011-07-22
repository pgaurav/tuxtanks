#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

typedef std::map<std::string, unsigned int> TextureHash;
typedef std::map<std::string, unsigned int>::iterator TextureHashIter;

SDL_Surface* loadImage(const std::string& imgfile);

void addTexture(const std::string& id, const std::string& img, TextureHash& texhash);

void deleteTexture(const std::string& id, TextureHash& texhash);

void deleteTextures(TextureHash& texhash);

#endif // TEXTURE_H
