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
		SDL_Surface* unit_surface = SDL_LoadBMP("images\\paladin_m.bmp");
		SDL_SetColorKey(unit_surface,SDL_TRUE,SDL_MapRGB(unit_surface->format,0,0,0));
		unit_texture = SDL_CreateTextureFromSurface(renderer,unit_surface);
		SDL_FreeSurface(unit_surface);

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

		rectChar.w = (int)(BOARD_BLOCK_SIZE)*xScale;
		rectChar.h = (int)(BOARD_BLOCK_SIZE)*yScale;

	    if (unit->isAnimating()) {
	    	std::cout << "IS ANIMATING" << std::endl;
	    	Animation* animation = unit->getAnimation();
	    	//animation.debug_showStats();
	    	std::cout << "CURRENT FRAME " << animation->currentFrame << std::endl;
	    	std::cout << "CURRENT FRAME/DURATION " << animation->currentFrame/animation->duration << std::endl;
	    	float diffX = animation->startPoint.x + (animation->currentFrame/animation->duration)* (animation->endPoint.x - animation->startPoint.x);
	    	float diffY = animation->startPoint.y + (animation->currentFrame/animation->duration)* (animation->endPoint.y - animation->startPoint.y);
	    	std::cout <<  "DIFF X: " << diffX << std::endl;
	    	std::cout <<  "DIFF Y: " << diffY << std::endl;
			rectChar.x = (int)(BOARD_INITIAL_X + ( diffX )* BOARD_BLOCK_SIZE)*xScale;
			rectChar.y = (int)(BOARD_INITIAL_Y + ( diffY )* BOARD_BLOCK_SIZE)*yScale;

			std::cout << "Animate rectChar.x=" << rectChar.x << std::endl;
			std::cout << "Animate rectChar.y=" << rectChar.y << std::endl;

			animation->currentFrame++;
		} else {

			rectChar.x = (int)(BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE)*xScale;
			rectChar.y = (int)(BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE)*yScale;

		}

	    SDL_Rect src;
	    src.x=0;
	    src.y=0;
	    src.w=32;
	    src.h=40;

	    if(unit->getTeam() == TEAM_B)
	    	SDL_RenderCopy(renderer, unit_texture, &src, &rectChar);
	    else
	    	SDL_RenderCopyEx(renderer,unit_texture,&src,&rectChar,0.0,NULL,SDL_FLIP_HORIZONTAL);

		SDL_Rect healthBar;
		healthBar.w = rectChar.w - 20;
		healthBar.h = 5;

		healthBar.x = rectChar.x + (rectChar.w - healthBar.w)/2;
		healthBar.y = rectChar.y;

		SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer,&healthBar);

		healthBar.w = (unit->getHp() * healthBar.w) / unit->getMaxHp();

		SDL_SetRenderDrawColor(renderer,0,255,0,SDL_ALPHA_OPAQUE);

		SDL_RenderFillRect(renderer,&healthBar);

	}

	void drawHighlightedArea(SDL_Renderer *renderer, Board* board, BOARD_AOE* area){

		setScale();

		SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor(renderer,0,0,255,150);

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
		    rect.x = (int)(BOARD_INITIAL_X + 1 + area->x*BOARD_BLOCK_SIZE)*xScale;
		    rect.y = (int)(BOARD_INITIAL_Y + 1 + area->y*BOARD_BLOCK_SIZE)*yScale;
			rect.w = (int)BOARD_BLOCK_SIZE*xScale;
			rect.h = (int)BOARD_BLOCK_SIZE*yScale;

			for (int x = ix; x <= fx; x++){
				rect.x = (int)(BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale;
				SDL_RenderFillRect(renderer,&rect);
			}

		    rect.x = (int)(BOARD_INITIAL_X + area->x*BOARD_BLOCK_SIZE)*xScale;

			for (int y = iy; y <= fy; y++){
				rect.y = (int)(BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale;
				SDL_RenderFillRect(renderer,&rect);
			}
		}

	}

}
