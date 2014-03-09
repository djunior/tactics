/*
 * drawFunctions.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: djunior
 */

#include "drawFunctions.h"

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
	std::cout << "Pintando unidade" << std::endl;

	unit->debug_showStats();

	std::cout << "Unit x=" << unit->getX() << std::endl;
	std::cout << "Block size=" << BOARD_BLOCK_SIZE << std::endl;
	std::cout << "Initial x=" << BOARD_INITIAL_X << std::endl;

    SDL_Rect rect;
	SDL_Color text_color = {255, 255, 255};
	string text = "Teste";
	int w,h;

    SDL_Surface *tSurface = textContent(font,const_cast<char*>(text.c_str()),text_color);
    SDL_Texture *tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);

    rect.x = BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE;
    rect.y = BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE;
    rect.w = w;
    rect.y = h;

    SDL_FreeSurface(tSurface);

	SDL_RenderCopy(renderer, tTexture, NULL, &rect);
}
