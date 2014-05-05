/*
 * drawFunctions.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: djunior
 */

#include "drawFunctions.h"

namespace Screen {

	SDL_Texture* background_texture, *broken_image_texture;
	SDL_Window* window;
	float xScale,yScale;
	bool isInitialized = false;
	std::map<std::string,SDL_Texture*> imageMap;

	SDL_Texture* loadSprite(SDL_Renderer* renderer,std::string imageURI){

		std::map<std::string,SDL_Texture*>::iterator it = imageMap.find(imageURI);

		if (it != imageMap.end()){
			return it->second;
		}

		SDL_Surface* s = SDL_LoadBMP(const_cast<char*>(imageURI.c_str()));
		if (s == NULL) {
			std::cerr << "Screen::loadSprite(): Failed to load image " << imageURI << ": failed to create SDL_Surface" << std::endl;
			return broken_image_texture;
		}

		SDL_SetColorKey(s,SDL_TRUE,SDL_MapRGB(s->format,0,0,0));
		SDL_Texture* t = SDL_CreateTextureFromSurface(renderer,s);
		SDL_FreeSurface(s);

		if (t == NULL){
			std::cerr << "Screen::loadSprite(): Failed to load image " << imageURI << ": failed to create SDL_Texture" << std::endl;
			return broken_image_texture;
		}

		imageMap.insert(std::pair<std::string,SDL_Texture*>(imageURI,t));
		return t;
	}

	SDL_Texture* loadImage(SDL_Renderer* renderer, std::string imageURI){
		SDL_Texture *t = IMG_LoadTexture(renderer,const_cast<char*>(imageURI.c_str()));
		if (t == NULL){
			std::cerr << "Screen::loadImage(): Failed to load image " << imageURI << ": failed to create SDL_Texture" << std::endl;
			return broken_image_texture;
		}

		imageMap.insert(std::pair<std::string,SDL_Texture*>(imageURI,t));
		return t;
	}

	void setScale()
		{
			int wWindow,hWindow;
			SDL_GetWindowSize(window,&wWindow,&hWindow);
			xScale = (float)wWindow/WINDOW_INITIAL_W;
			yScale = (float)hWindow/WINDOW_INITIAL_H;
		}

	void init(SDL_Renderer* renderer,SDL_Window* win){
		broken_image_texture = IMG_LoadTexture(renderer,BROKEN_IMAGE);
		background_texture = IMG_LoadTexture(renderer, "images\\FFIV_PSP_Forest_Battle.png");

		window = win;
		setScale();

		isInitialized = true;
	}	

	void cleanup(){
		// Destruindo texturas criadas individualmente
		SDL_DestroyTexture(background_texture);
		SDL_DestroyTexture(broken_image_texture);

		// Destruindo texturas criadas pela funcao loadSprite
		for (std::map<std::string,SDL_Texture*>::iterator it = imageMap.begin(); it != imageMap.end(); it++){
			SDL_DestroyTexture(it->second);
		}

		// Zerando o mapa imageMap
		imageMap.clear();
	}

	void drawBoard(SDL_Renderer *renderer, Board* board) {

		setScale();

		int x = static_cast<int>(BOARD_INITIAL_X*xScale);
		int y = static_cast<int>(BOARD_INITIAL_Y*yScale);

		int endX = static_cast<int>((BOARD_INITIAL_X + BOARD_BLOCK_SIZE*board->getMaxBoardX())*xScale);
		int endY = static_cast<int>((BOARD_INITIAL_Y + BOARD_BLOCK_SIZE*board->getMaxBoardY())*yScale);

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
			unsigned int xi = x+static_cast<int>((BOARD_BLOCK_SIZE*i)*xScale);
			SDL_RenderDrawLine(renderer,xi,y,xi,endY);
		}

		for (unsigned int i=1; i < board->getMaxBoardY();i++){
			unsigned int yi = y+static_cast<int>((BOARD_BLOCK_SIZE*i)*yScale);
			SDL_RenderDrawLine(renderer,x,yi,endX,yi);
		}
	}

	int getScreenBoardX(int x){
		return static_cast<int>((BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale);
	}

	int getScreenBoardY(int y){
		return static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
	}

	void drawUnit(Unit *unit,SDL_Texture* texture, SDL_Renderer *renderer, TTF_Font *font){
		if (! isInitialized) {
			std::cerr << "Falha a pintar a unidade " << unit << std::endl;
			std::cerr << "A funcao Screen::init nao foi invocada" << std::endl;
			return;
		}

		int w = 0;
		int h = 0;
		SDL_Rect srcChar,srcLeftArm, srcRightArm,rectChar,destArm;

	    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	    rectChar.x = static_cast<int>((BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE)*xScale);
	    rectChar.y = static_cast<int>((BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE)*yScale);
	    rectChar.w = static_cast<int>((BOARD_BLOCK_SIZE)*xScale);
	    rectChar.h = static_cast<int>((BOARD_BLOCK_SIZE)*yScale);

	    srcChar.y=0;
	    srcChar.w=32;
	    srcChar.h=40;

	    srcLeftArm.w = 24;
	    srcLeftArm.h = 23;

	    srcRightArm.w = 24;
	    srcRightArm.h = 23;

    	float w_percent = static_cast<float>(srcRightArm.w) / static_cast<float>(srcChar.w);
    	float h_percent = static_cast<float>(srcRightArm.h) / static_cast<float>(srcChar.h);

    	destArm.w = rectChar.w * w_percent;
    	destArm.h = rectChar.h * h_percent;

	    if (unit->isAnimating()) {

	    	Animation* animation = unit->getAnimation();

	    	float diffX = animation->startPoint.x + (animation->currentFrame/animation->duration)* (animation->endPoint.x - animation->startPoint.x);
	    	float diffY = animation->startPoint.y + (animation->currentFrame/animation->duration)* (animation->endPoint.y - animation->startPoint.y);

			rectChar.x = static_cast<int>((BOARD_INITIAL_X + ( diffX )* BOARD_BLOCK_SIZE)*xScale);
			rectChar.y = static_cast<int>((BOARD_INITIAL_Y + ( diffY )* BOARD_BLOCK_SIZE)*yScale);

			if (animation->type == ANIMATION_UNIT_MOVE){
				int index = ((int) animation->currentFrame) % (5 * animation->repeatFrame) / animation->repeatFrame;
				int armIndex = ((int) animation->currentFrame) % (3 * animation->repeatFrame) / animation->repeatFrame;


				std::cout << "sin(armIndex*2*M_PI/3)= " << sin(armIndex*2*M_PI/3) << std::endl;
				std::cout << "sin(armIndex*2*M_PI/3)*3/2= " << sin(armIndex*2*M_PI/3)*3/2 << std::endl;
				std::cout << "sin(armIndex*2*M_PI/3)*(3/2) + (3/2)= " << sin(armIndex*2*M_PI/3)*(3/2) + (3/2) << std::endl;

			    armIndex = sin(armIndex*2*M_PI/3)*(3/2) + (3/2);

				if (unit->getTeam() == TEAM_A) {

					if (index <= 3) {
						srcChar.y = srcChar.h;
						srcChar.x = srcChar.w*(3+index);
					} else {
						srcChar.y = srcChar.h*2;
						srcChar.x = 0;
					}

					srcLeftArm.y = 80 + srcLeftArm.h;
					srcRightArm.y = 80 + srcRightArm.h;

				} else {

					if (index <= 1) {
						srcChar.y = 0;
						srcChar.x = srcChar.w*(5 + index);
					} else {
						srcChar.y = srcChar.h;
						srcChar.x = srcChar.w*(index -2);
					}

					srcLeftArm.y = 80;
					srcRightArm.y = 80;
				}
				std::cout << "ARM INDEX: " << 1 - armIndex << std::endl;
				armIndex = 2*(1 - armIndex);
				srcLeftArm.x = 32 + srcLeftArm.w*(2 + armIndex);
				srcRightArm.x = 32 + srcRightArm.w*(3 + armIndex);

			} else if (animation->type == ANIMATION_UNIT_ATTACK){

				int armIndex = ((int) animation->currentFrame) % (5 * animation->repeatFrame) / animation->repeatFrame;



			}

			animation->currentFrame++;
		} else {

			rectChar.x = static_cast<int>((BOARD_INITIAL_X + unit->getX()*BOARD_BLOCK_SIZE)*xScale);
			rectChar.y = static_cast<int>((BOARD_INITIAL_Y + unit->getY()*BOARD_BLOCK_SIZE)*yScale);

			if (unit->getTeam() == TEAM_A)
				srcChar.x=srcChar.w*3;
			else
			    srcChar.x=srcChar.w;
		}

    	destArm.x = rectChar.x + rectChar.w - destArm.w;
    	if (unit->getSprite()->getType() == SPRITE_TYPE_2){
    		destArm.x += 5;
    	}

    	destArm.y = rectChar.y + rectChar.h/3 - 3;

    	SDL_Rect destLeftArm;
    	destLeftArm.w = destArm.w;
    	destLeftArm.h = destArm.h;
    	destLeftArm.y = destArm.y - 8;
    	destLeftArm.x = rectChar.x + 8;

	    if(unit->getTeam() == TEAM_B) {
	    	SDL_RenderCopy(renderer, texture, &srcLeftArm, &destLeftArm);
	    	SDL_RenderCopy(renderer, texture, &srcChar, &rectChar);
	    	SDL_RenderCopy(renderer, texture, &srcRightArm, &destArm);
	    } else {
	    	SDL_RenderCopyEx(renderer, texture, &srcLeftArm, &destLeftArm,0.0,NULL,SDL_FLIP_HORIZONTAL);
	    	SDL_RenderCopyEx(renderer,texture,&srcChar,&rectChar,0.0,NULL,SDL_FLIP_HORIZONTAL);
	    	SDL_RenderCopyEx(renderer, texture, &srcRightArm, &destArm,0.0,NULL,SDL_FLIP_HORIZONTAL);
	    }

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

	void drawUnit(Unit *unit, SDL_Renderer *renderer, TTF_Font *font){
		drawUnit(unit,loadSprite(renderer,unit->getImage()),renderer,font);
	}

	void drawEndGame(T_TEAM winningTeam, int turn){
	}

	void drawHighlightedArea(SDL_Renderer *renderer, Board* board, BOARD_AOE* area, GAMEMANAGER_CONTEXT context){
		setScale();

		SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

		if (context == CONTEXT_UNIT_SELECT_MOVE)
		{
			SDL_SetRenderDrawColor(renderer,0,0,255,150);
		}
		else if (context == CONTEXT_IDLE)
		{
			SDL_SetRenderDrawColor(renderer,255,215,0,150);
		}
		else if (context == CONTEXT_UNIT_SELECT_TARGET)
		{
			SDL_SetRenderDrawColor(renderer,255,69,0,150);
		}
		else if (context == CONTEXT_UNIT_MENU){
			SDL_SetRenderDrawColor(renderer,255,255,255,150);
		}

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
	    rect.x = static_cast<int>((BOARD_INITIAL_X + 1 + area->x*BOARD_BLOCK_SIZE)*xScale);
	    rect.y = static_cast<int>((BOARD_INITIAL_Y + 1 + area->y*BOARD_BLOCK_SIZE)*yScale);
		rect.w = static_cast<int>(BOARD_BLOCK_SIZE*xScale);
		rect.h = static_cast<int>(BOARD_BLOCK_SIZE*yScale);

		if (area->shape == AOE_SHAPE_POINT) {
			SDL_RenderFillRect(renderer,&rect);

		} else if (area->shape == AOE_SHAPE_CROSS){
			for (int x = ix; x <= fx; x++){
				rect.x = static_cast<int>((BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale);
				SDL_RenderFillRect(renderer,&rect);
			}

		    rect.x = static_cast<int>((BOARD_INITIAL_X + area->x*BOARD_BLOCK_SIZE)*xScale);

			for (int y = iy; y <= fy; y++){
				rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
				SDL_RenderFillRect(renderer,&rect);
			}
		} else if (area->shape == AOE_SHAPE_SQUARE){
			for (int x = ix; x <= fx; x++){
				for (int y = iy; y <= fy; y++){
					rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
					rect.x = static_cast<int>((BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale);
					SDL_RenderFillRect(renderer,&rect);
				}
			}
		} else if (area->shape == AOE_SHAPE_CIRCLE){
			int lx = area->x + area->range;
			int ly = area->y + area->range;
			int mx = area->x;
			int my = area->y;
			int cx = 0;
			int cy = 0;
			for (int x = mx; x <= lx; x++){
				for (int y = my; y <= ly; y++){
					if(cy + cx <= area->range)
					{
						rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
						rect.x = static_cast<int>((BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale);
						if (y <= fy && x <= fx)
						{
							SDL_RenderFillRect(renderer,&rect);
						}
						if(cy != 0 && (y-2*cy) >= 0 && (y-2*cy) <= fy)
						{
							rect.y = static_cast<int>((BOARD_INITIAL_Y + (y-2*cy)*BOARD_BLOCK_SIZE)*yScale);
							if (x <= fx)
							{
								SDL_RenderFillRect(renderer,&rect);
							}
						}
						if(cx != 0 && (x-2*cx) >= 0)
						{
							rect.x = static_cast<int>((BOARD_INITIAL_X + (x-2*cx)*BOARD_BLOCK_SIZE)*xScale);
							if ((x-2*cx) <= fx)
							{
								SDL_RenderFillRect(renderer,&rect);
							}
							if(cy != 0 && rect.y != static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale) && y <= fy)
							{
								rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
								SDL_RenderFillRect(renderer,&rect);
							}
						}

					}
					cy++;
				}
				cx++;
				cy = 0;
			}
		}
	}

	T_ERROR mouseBoardPosition(Board* board, BOARD_AOE* area) {

		SDL_Rect rect;
	    rect.x = static_cast<int>((BOARD_INITIAL_X)*xScale);
	    rect.y = static_cast<int>((BOARD_INITIAL_Y)*yScale);
		rect.w = static_cast<int>((board->getMaxBoardX()*BOARD_BLOCK_SIZE)*xScale);
		rect.h = static_cast<int>((board->getMaxBoardY()*BOARD_BLOCK_SIZE)*yScale);

		int mouse_x,mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);		

		if (!hit(rect)){
			return T_ERROR_OUT_OF_BOUNDS;
		}

		rect.w = static_cast<int>(BOARD_BLOCK_SIZE*xScale);
		rect.h = static_cast<int>(BOARD_BLOCK_SIZE*yScale);

		for (int x = 0; x <= board->getMaxBoardX()-1; x++){
			for (int y = 0; y <= board->getMaxBoardY()-1; y++){
				rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
				rect.x = static_cast<int>((BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale);
				if(hit(rect)){
					area->x = x;
					area->y = y;
					area->range = 0;
					area->shape = AOE_SHAPE_POINT;
					return T_SUCCESS;
				}
			}
		}
		return T_ERROR_UNKNOWN;
	}

	T_ERROR mouseCheckArea(Board* board, BOARD_AOE* area, BOARD_AOE* mouse) {

		T_ERROR e = mouseBoardPosition(board,mouse);

		if (e != T_SUCCESS)
			return e;

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

		if (area->shape == AOE_SHAPE_POINT) {
			if(mouse->x == area->x && mouse->y == area->y)
				return T_SUCCESS;
			else
				return T_ERROR_OUT_OF_RANGE;

		} else if (area->shape == AOE_SHAPE_CROSS){
			for (int x = ix; x <= fx; x++){
				if(mouse->x == x && mouse->y == area->y)
					return T_SUCCESS;
			}

			for (int y = iy; y <= fy; y++){
				if(mouse->x == area->x && mouse->y == y)
					return T_SUCCESS;
			}
			return T_ERROR_OUT_OF_RANGE;

		} else if (area->shape == AOE_SHAPE_SQUARE){
			for (int x = ix; x <= fx; x++){
				for (int y = iy; y <= fy; y++){
					if(mouse->x == x && mouse->y == y)
						return T_SUCCESS;
				}
			}
			return T_ERROR_OUT_OF_RANGE;

		} else if (area->shape == AOE_SHAPE_CIRCLE){

			SDL_Rect rect;
		    rect.x = static_cast<int>((BOARD_INITIAL_X + 1 + area->x*BOARD_BLOCK_SIZE)*xScale);
		    rect.y = static_cast<int>((BOARD_INITIAL_Y + 1 + area->y*BOARD_BLOCK_SIZE)*yScale);
			rect.w = static_cast<int>(BOARD_BLOCK_SIZE*xScale);
			rect.h = static_cast<int>(BOARD_BLOCK_SIZE*yScale);
			
			int lx = area->x + area->range;
			int ly = area->y + area->range;
			int mx = area->x;
			int my = area->y;
			int cx = 0;
			int cy = 0;
			for (int x = mx; x <= lx; x++){
				for (int y = my; y <= ly; y++){
					if(cy + cx <= area->range)
					{
						rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
						rect.x = static_cast<int>((BOARD_INITIAL_X + x*BOARD_BLOCK_SIZE)*xScale);
						if (y <= fy && x <= fx)
						{
							if(mouse->x == x && mouse->y == y)
								return T_SUCCESS;
						}
						if(cy != 0 && (y-2*cy) >= 0 && (y-2*cy) <= fy)
						{
							rect.y = static_cast<int>((BOARD_INITIAL_Y + (y-2*cy)*BOARD_BLOCK_SIZE)*yScale);
							if (x <= fx)
							{
								if(mouse->x == x && mouse->y == (y-2*cy))
									return T_SUCCESS;
							}
						}
						if(cx != 0 && (x-2*cx) >= 0)
						{
							rect.x = static_cast<int>((BOARD_INITIAL_X + (x-2*cx)*BOARD_BLOCK_SIZE)*xScale);
							if ((x-2*cx) <= fx)
							{
								if(mouse->x == (x-2*cx) && mouse->y == y)
									return T_SUCCESS;
							}
							if(cy != 0 && rect.y != static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale) && y <= fy)
							{
								rect.y = static_cast<int>((BOARD_INITIAL_Y + y*BOARD_BLOCK_SIZE)*yScale);
								if(mouse->x == (x-2*cx) && mouse->y == y)
									return T_SUCCESS;
							}
						}

					}
					cy++;
				}
				cx++;
				cy = 0;
			}
			return T_ERROR_OUT_OF_RANGE;
		}
	}

}
