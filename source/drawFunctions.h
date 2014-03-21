/*
 * drawFunctions.h
 *
 *  Created on: Mar 4, 2014
 *      Author: djunior
 */

#ifndef DRAWFUNCTIONS_H_
#define DRAWFUNCTIONS_H_

#include "board.h"
#include "unit.h"

#include "basic_includes.h"
#include "fps.h"

#define BOARD_INITIAL_X 250
#define BOARD_INITIAL_Y 230
#define BOARD_BLOCK_SIZE 100
#define SPRITE_UNIT "images\\char_lanca.png"

namespace Screen {
	extern void setScale();
	extern void init(SDL_Renderer*, SDL_Window*);
	extern void drawBoard(SDL_Renderer*, Board*);
	extern void drawHighlightedArea(SDL_Renderer*, Board*, BOARD_AOE*);
	extern void drawUnit(Unit*, SDL_Renderer*, TTF_Font*);
//	void drawUnit(Knight*, SDL_Renderer*, TTF_Font*);
//	void drawUnit(Wizard*, SDL_Renderer*, TTF_Font*);
}
#endif /* DRAWFUNCTIONS_H_ */
