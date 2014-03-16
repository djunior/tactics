/*
 * drawFunctions.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: djunior
 */

#include "drawFunctions.h"

namespace Screen {

	SDL_Texture* unit_texture, *background_texture;
	SDL_Window* window;
	float xScale,yScale;
	bool isInitialized = false;

	void setScale()
		{
			int wWindow,hWindow;
			SDL_GetWindowSize(window,&wWindow,&hWindow);
			xScale = (float)wWindow/WINDOW_INITIAL_W;
			yScale = (float)hWindow/WINDOW_INITIAL_H;
		}

	void init(SDL_Renderer* renderer,SDL_Window* win){
		unit_texture = IMG_LoadTexture(renderer, "images\\char_lanca.png");
		background_texture = IMG_LoadTexture(renderer, "images\\FFIV_PSP_Forest_Battle.png");
		window = win;
		setScale();

		isInitialized = true;
	}	

	void drawBoard(SDL_Renderer *renderer, Board* board) {

		setScale();

		int x = (int)BOARD_INITIAL_X*xScale;
		int y = (int)BOARD_INITIAL_Y*yScale;

		int endX = (int)(BOARD_INITIAL_X + BOARD_BLOCK_SIZE*board->getMaxBoardX())*xScale;
		int endY = (int)(BOARD_INITIAL_Y + BOARD_BLOCK_SIZE*board->getMaxBoardY())*yScale;

		SDL_Rect rect;

	    rect.x = 0;
	    rect.y = 0;
	    rect.w = WINDOW_INITIAL_W;
	    rect.h = WINDOW_INITIAL_H;

	    SDL_RenderCopy(renderer, background_texture, NULL, NULL);

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
			unsigned int xi = x+(int)(BOARD_BLOCK_SIZE*i)*xScale;
			SDL_RenderDrawLine(renderer,xi,y,xi,endY);
		}

		for (unsigned int i=1; i < board->getMaxBoardY();i++){
			unsigned int yi = y+(int)(BOARD_BLOCK_SIZE*i)*yScale;
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

	    rectChar.x = (int)(BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE)*xScale;
	    rectChar.y = (int)(BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE)*yScale;
	    rectChar.w = (int)(BOARD_BLOCK_SIZE)*xScale;
	    rectChar.h = (int)(BOARD_BLOCK_SIZE)*yScale;

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

		setScale();

		SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor(renderer,0,0,255,170);

		if (area->shape == AOE_SHAPE_CROSS){

			int ix = area->x - area->range;
			if (ix < 0)
				ix = 0;

			int iy = area->y - area->range;
			if (iy < 0)
				iy = 0;

			int fx = area->x + area->range;
			if (fx >= board->getMaxBoardX())
				fx = board->getMaxBoardX() - 1;

			int fy = area->y + area->range;
			if (fy >= board->getMaxBoardY())
				fy = board->getMaxBoardY() - 1;

			SDL_Rect rect;
		    rect.x = (int)(BOARD_INITIAL_X + 5 + area->x*BOARD_BLOCK_SIZE)*xScale;
		    rect.y = (int)(BOARD_INITIAL_Y + 5 + area->y*BOARD_BLOCK_SIZE)*yScale;
			rect.w = (int)(BOARD_BLOCK_SIZE - 10)*xScale;
			rect.h = (int)(BOARD_BLOCK_SIZE - 10)*yScale;

			for (int x = ix; x <= fx; x++){
				rect.x = (int)(BOARD_INITIAL_X + 5 + x*BOARD_BLOCK_SIZE)*xScale;
				SDL_RenderFillRect(renderer,&rect);
			}

		    rect.x = (int)(BOARD_INITIAL_X + 5 + area->x*BOARD_BLOCK_SIZE)*xScale;

			for (int y = iy; y <= fy; y++){
				rect.y = (int)(BOARD_INITIAL_Y + 5 + y*BOARD_BLOCK_SIZE)*yScale;
				SDL_RenderFillRect(renderer,&rect);
			}

		}

	}

}
