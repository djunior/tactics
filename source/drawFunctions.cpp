/*
 * drawFunctions.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: djunior
 */

#include "drawFunctions.h"

namespace Screen {

SDL_Texture* unit_texture, *background_texture;
bool isInitialized = false;

void init(SDL_Renderer* renderer){
	unit_texture = IMG_LoadTexture(renderer, "images\\char_lanca.png");
	background_texture = IMG_LoadTexture(renderer, "images\\FFIV_PSP_Forest_Battle.png");

	isInitialized = true;
}

void drawBoard(SDL_Renderer *renderer, Board* board) {
	int x = BOARD_INITIAL_X;
	int y = BOARD_INITIAL_Y;

	int endX = BOARD_INITIAL_X + BOARD_BLOCK_SIZE*board->getMaxBoardX();
	int endY = BOARD_INITIAL_Y + BOARD_BLOCK_SIZE*board->getMaxBoardY();

	SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 1280;
    rect.h = 720;

    SDL_RenderCopy(renderer, background_texture, NULL, &rect);

	SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);

	// Linha no eixo x
	SDL_RenderDrawLine(renderer,x,y,endX,y);

	// Linha no eixo y
	SDL_RenderDrawLine(renderer,x,y,x,endY);

	// Linha paralela ao eixo x, deslocada de endX
	SDL_RenderDrawLine(renderer,endX,y,endX,endY);

	// Linha paralela ao eixo y, deslocada de endY
	SDL_RenderDrawLine(renderer,x,endY,endX,endY);

	for (unsigned int i=1; i < board->getMaxBoardX();i++){
		unsigned int xi = x+BOARD_BLOCK_SIZE*i;
		SDL_RenderDrawLine(renderer,xi,y,xi,endY);
	}

	for (unsigned int i=1; i < board->getMaxBoardY();i++){
		unsigned int yi = y+BOARD_BLOCK_SIZE*i;
		SDL_RenderDrawLine(renderer,x,yi,endX,yi);
	}
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

    rectChar.x = BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE;
    rectChar.y = BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE;
    rectChar.w = BOARD_BLOCK_SIZE;
    rectChar.h = BOARD_BLOCK_SIZE;

    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=w/4;
    src.h=h/2;

    SDL_RenderCopy(renderer, unit_texture, &src, &rectChar);

	SDL_Rect healthBar;
	healthBar.w = rectChar.w - 20;
	healthBar.h = 5;

	healthBar.x = rectChar.x + (rectChar.w - healthBar.w)/2;
	healthBar.y = rectChar.y;

	SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE);
/*
	std::cout << "HEALTH BAR *" << &healthBar << std::endl;
	std::cout << "x=" << healthBar.x << " y= " << healthBar.y << std::endl;
	std::cout << "w=" << healthBar.w << " h= " << healthBar.h << std::endl;
*/
	SDL_RenderFillRect(renderer,&healthBar);

	healthBar.w = (unit->getHp() * healthBar.w) / unit->getMaxHp();

	SDL_SetRenderDrawColor(renderer,0,255,0,SDL_ALPHA_OPAQUE);

	SDL_RenderFillRect(renderer,&healthBar);

}

void drawHighlightedArea(SDL_Renderer *renderer, Board* board, BOARD_AOE* area){

	SDL_SetRenderDrawColor(renderer,0,0,255,150);
	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

	if (area->shape == AOE_SHAPE_CROSS){

		int ix = area->x - area->range;
		if (ix < 0)
			ix = 0;

		int iy = area->y - area->range;
		if (iy < 0)
			iy = 0;

		int fx = area->x + area->range;
		if (fx >= board->getMaxBoardX())
			fx = board->getMaxBoardX()-1;

		int fy = area->y + area->range;
		if (fy >= board->getMaxBoardY())
			fy = board->getMaxBoardY()-1;

		SDL_Rect rect;
	    rect.x = BOARD_INITIAL_X + 1 + area->x*BOARD_BLOCK_SIZE;
	    rect.y = BOARD_INITIAL_Y + 1 + area->y*BOARD_BLOCK_SIZE;
		rect.w = BOARD_BLOCK_SIZE;
		rect.h = BOARD_BLOCK_SIZE;

		for (int x = ix; x <= fx; x++){
			rect.x = BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE;
			SDL_RenderFillRect(renderer,&rect);
		}

	    rect.x = BOARD_INITIAL_X + area->x*BOARD_BLOCK_SIZE;

		for (int y = iy; y <= fy; y++){
			if (y != area->y){
				rect.y = BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE;
				SDL_RenderFillRect(renderer,&rect);
			}
		}

	}

}

}
