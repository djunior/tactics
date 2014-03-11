/*
 * drawFunctions.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: djunior
 */

#include "drawFunctions.h"

namespace Screen {

SDL_Texture* unit_texture;
bool isInitialized = false;

void init(SDL_Renderer* renderer){
	unit_texture = IMG_LoadTexture(renderer, "images\\char_lanca.png");

	isInitialized = true;
}

void drawBoard(SDL_Renderer *renderer, Board* board) {
//	int x = BOARD_INITIAL_X;
//	int y = BOARD_INITIAL_Y;
//
//	int endX = BOARD_INITIAL_X + BOARD_BLOCK_SIZE*board->getMaxBoardX();
//	int endY = BOARD_INITIAL_Y + BOARD_BLOCK_SIZE*board->getMaxBoardY();

//	SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
//
//	// Linha no eixo x
//	SDL_RenderDrawLine(renderer,x,y,endX,y);
//
//	// Linha no eixo y
//	SDL_RenderDrawLine(renderer,x,y,x,endY);
//
//	// Linha paralela ao eixo x, deslocada de endX
//	SDL_RenderDrawLine(renderer,endX,y,endX,endY);
//
//	// Linha paralela ao eixo y, deslocada de endY
//	SDL_RenderDrawLine(renderer,x,endY,endX,endY);
//
//	SDL_RenderPresent(renderer);


//    tSurface = textContent(font,const_cast<char*>(text.c_str()),text_color);
//    tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
//    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);
}

void drawUnit(Unit* unit, SDL_Renderer *renderer, TTF_Font *font){
	if (! isInitialized) {
		std::cerr << "Falha a pintar a unidade " << unit << std::endl;
		std::cerr << "A funcao Screen::init nao foi invocada" << std::endl;
		return;
	}

	int w = 0;
	int h = 0;
	SDL_Rect rectChar;

    SDL_QueryTexture(unit_texture, NULL, NULL, &w, &h);
    // TODO: Inverter o X e Y do Board
    rectChar.y = BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE;
    rectChar.x = BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE;
    rectChar.w = BOARD_BLOCK_SIZE;
    rectChar.h = BOARD_BLOCK_SIZE;

    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=w/4;
    src.h=h/2;

    SDL_RenderCopy(renderer, unit_texture, &src, &rectChar);
}

}
