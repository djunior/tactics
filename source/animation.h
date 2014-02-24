#ifndef animation_h
#define animation_h

#include "basic_includes.h"

void sdlInit();
void textInit();
TTF_Font *loadFont();
SDL_Surface *textContent(TTF_Font *,char *,SDL_Color);

class framesPerSecond
{
	private:
		int _frames;
		time_t _start;
		time_t _end;
		double _loop;
		float _fps;
		SDL_Rect _rect;

	public:
		//CONSTRUTOR:
		framesPerSecond(void);
		// SET Variables:
		void frames(int);
		// GET Variables:
		int frames();
		SDL_Rect rect();
		time_t start();
		time_t end();
		double loop();

		//FUNCTIONS:
		void plus();
		double calculate();
		SDL_Texture *show(SDL_Renderer*, TTF_Font *);
};

#endif