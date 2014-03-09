#ifndef animation_h
#define animation_h

#include "basic_includes.h"

void sdlInit();
void textInit();
void loadFont(TTF_Font **);
SDL_Surface *textContent(TTF_Font *,char *,SDL_Color);

class framesPerSecond
{
	private:
		int frames;
		time_t start;
		time_t end;
		double loop;
		float fps;
		SDL_Rect rect;
		float lastTick;
		float frameDuration;

	public:
		//CONSTRUTOR:
		framesPerSecond(void);
		// SET Variables:
		void setFrames(int);
		time_t setStart();
		time_t setEnd();
		// GET Variables:
		int getFrames();
		SDL_Rect getRect();
		double getLoop();

		//FUNCTIONS:
		void plus();
		double calculate();
		SDL_Texture *show(SDL_Renderer*, TTF_Font *);
		void fpsControl(int limit_fps);
		bool isFrameDone();
};

#endif
