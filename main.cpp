#include <iostream>
#include <string>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "welcomeanim.h"
#include "introanim.h"
#include "gamedata.h"
#include "audio.h"

#define NUM_ANIMATIONS 4

void frameDelay()
{
	const int tickInterval = 30; 
	static int nextTick = 0;
	int curTick = SDL_GetTicks();
	if(curTick >= nextTick) nextTick = curTick + tickInterval;
	SDL_Delay(nextTick - curTick);
}

void initGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void clear()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv, char **env)
{
	int err = 0;
	const int w = 800;
	const int h = 600;
	const int bpp = 32;
	const int flags = SDL_OPENGL;
	bool running = true;
	std::string caption = "Tuxtanks - A battle game of tanks!";
	err = SDL_Init(SDL_INIT_EVERYTHING);
	if(err < 0) 
	{
		std::cerr << "error: Initializing SDL" << std::endl;
		exit(1);
	}
    	SDL_EnableUNICODE(1);
    	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_Surface *surface = SDL_SetVideoMode(w, h, bpp, SDL_OPENGL);
	SDL_Surface *icon = SDL_LoadBMP("images/icon.bmp");
	SDL_WM_SetCaption(caption.c_str(), "");
	SDL_WM_SetIcon(icon, NULL);
	// atexit(SDL_Quit);
	Audio *audio = new Audio();
	audio->addMusic("background", "audio/background.wav");
	audio->addSound("click", "audio/click.wav");
	audio->addSound("keystroke", "audio/keystroke.wav");
	initGL(w, h);
	GameData gamedata;
	Animation *animation[NUM_ANIMATIONS]; 
	int curAnimation = 0;
	animation[0] = new WelcomeAnimation(&gamedata, audio, w, h);
	animation[1] = new IntroAnimation(&gamedata, audio, w, h);
	animation[2] = new WelcomeAnimation(&gamedata, audio, w, h);
	animation[3] = new WelcomeAnimation(&gamedata, audio, w, h);
	SDL_Event event;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				running = false;
			}
			if(event.type == SDL_KEYDOWN)
			{
				int key = event.key.keysym.sym;
				int mod = event.key.keysym.mod;
				if((mod & KMOD_CTRL) && (key == 'f' || key == 'F'))
				{
					SDL_WM_ToggleFullScreen(surface);
				}
			}
			int res = animation[curAnimation]->handleEvents(event);
			if(res == ANIMATION_EVENT_EXIT) 
			{
				running = false;
			}
			else if(res == ANIMATION_EVENT_PREV)
			{
				if(curAnimation > 0) --curAnimation;
			}
			else if(res == ANIMATION_EVENT_NEXT)
			{
				if(curAnimation < NUM_ANIMATIONS-1) ++curAnimation;
			}
			else // ANIMATION_EVENT_NONE
			{
				// do nothing
			}
		}
		clear();
		animation[curAnimation]->render();
		SDL_GL_SwapBuffers();
		frameDelay();
	}
	for(int i=0; i<NUM_ANIMATIONS; ++i) delete animation[i];
	SDL_FreeSurface(surface);
	SDL_FreeSurface(icon);
	delete audio;
	SDL_Quit();
	return 0;
}
