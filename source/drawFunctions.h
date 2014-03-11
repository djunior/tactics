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
#include "animation.h"

#define BOARD_INITIAL_X 300
#define BOARD_INITIAL_Y 100
#define BOARD_BLOCK_SIZE 80
#define SPRITE_UNIT "images\\char_lanca.png"

namespace Screen {
	extern void init(SDL_Renderer*);
	extern void drawBoard(SDL_Renderer*, Board*);
	extern void drawUnit(Unit*, SDL_Renderer*, TTF_Font*);
//	void drawUnit(Knight*, SDL_Renderer*, TTF_Font*);
//	void drawUnit(Wizard*, SDL_Renderer*, TTF_Font*);
}
#endif /* DRAWFUNCTIONS_H_ */
