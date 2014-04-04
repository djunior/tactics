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
#include "unit_class/wizard.h"
#include "unit_class/knight.h"

#include "basic_includes.h"
#include "fps.h"
#include <stdexcept>
#include <map>

#define BOARD_INITIAL_X 250
#define BOARD_INITIAL_Y 230
#define BOARD_BLOCK_SIZE 100

#define SPRITE_UNIT "images\\char_lanca.png"
#define BROKEN_IMAGE "images\\broken_image.png"

namespace Screen {
	extern SDL_Texture* loadSprite(SDL_Renderer* renderer,std::string imageURI);
	extern void setScale();
	extern void init(SDL_Renderer*, SDL_Window*);
	extern void drawBoard(SDL_Renderer*, Board*);
	extern void drawHighlightedArea(SDL_Renderer*, Board*, BOARD_AOE*);
	extern void drawUnit(Unit*,SDL_Texture*,SDL_Renderer*,TTF_Font*);
	extern void drawUnit(Unit*, SDL_Renderer*, TTF_Font*);
	extern void drawEndGame(T_TEAM,int);
	extern void cleanup();
}
#endif /* DRAWFUNCTIONS_H_ */
