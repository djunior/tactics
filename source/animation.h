#ifndef animation_h
#define animation_h

#include "basic_includes.h"

void sdlInit();
void textInit();
void loadFont(TTF_Font *font);
void textContent(TTF_Font *font,string text,SDL_Color text_color, SDL_Surface *textSurface);

#endif