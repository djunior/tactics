#ifndef animation_h
#define animation_h

#include "basic_includes.h"

void sdlInit();
void textInit();
TTF_Font *loadFont();
SDL_Surface *textContent(TTF_Font *font,const char *text,SDL_Color text_color);

#endif