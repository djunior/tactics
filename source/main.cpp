/*
 * main.c
 *
 *	Projeto Tactics
 *
 *  Created on: Feb 12, 2014
 *      Author: djunior
 */
#include "basic_includes.h"

#include "fps.h"
#include "menu.h"

#include "mouse.h"

#include "board.h"
#include "gameManager.h"
#include "gameConfig.h"
#include "unit.h"

#include "drawFunctions.h"

void setupGame(GameManager* gameManager, GameConfig* gameConfig){
	UNIT_LIST_VECTOR* unitList = gameConfig->getUnitList();

	if (unitList->empty())
		gameConfig->setupDefaultUnitList();

	for (std::vector<UNIT_PAIR>::iterator it=unitList->begin(); it != unitList->end(); it++){
		UNIT_PAIR p = *it;
		gameManager->createUnit(p.second,p.first);
	}

}

int main(int argc, char *argv[]){

    sdlInit();
    textInit();

    bool Starting = true;
    bool Running = false;
    SDL_Event Event;
    
    SDL_Renderer* renderer;
    TTF_Font *font;

    framesPerSecond fps;

    SDL_Window* window;
    int wWindow = WINDOW_INITIAL_W;
    int hWindow = WINDOW_INITIAL_H;
    int min_wWindow = WINDOW_MIN_W;
    int min_hWindow = WINDOW_MIN_H;
    // OnInit

    window = SDL_CreateWindow("Tactics", 100, 100, wWindow, hWindow, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC);
	if (window == 0){
		SDL_Quit();
		return 1;
	}

	SDL_SetWindowMinimumSize(window,min_wWindow,min_hWindow);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL){
        return 1;
    }

    Screen::init(renderer, window);

    Board gameBoard(8,4);
    GameManager gm(&gameBoard, renderer, window);
    GameConfig gc(renderer, window);

    //Load Content
    int x,y;

    loadFont(&font);  

    mWindow menu(font,renderer,window);
    
    // FPS Setup BEGIN
    fps.fpsControl(60);
    
    fps.setFrames(0);
    time_t hold;
    time_t actual;
    hold = fps.setStart();
    actual = hold;
    // FPS Setup END
    // Unit create BEGIN
//    gm.createUnit(UNIT_CLASS_WIZARD,TEAM_A);
//    gm.createUnit(UNIT_CLASS_WIZARD,TEAM_B);
//
//    gm.createUnit(UNIT_CLASS_KNIGHT,TEAM_A);
//    gm.createUnit(UNIT_CLASS_KNIGHT,TEAM_B);

    // Unit create END

   menu.mainMenu();
   bool close;
    while (Starting)
    {
    	if (fps.isFrameDone())
    	{
    	
	    	while(SDL_PollEvent(&Event))
			{
				switch(Event.type)
				{
					case SDL_QUIT:
						Running = false;
						Starting = false;
						break;

					case SDL_KEYDOWN:
						switch(Event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								Running = false;
								Starting = false;
								break;
						}
						break;

					case SDL_MOUSEBUTTONDOWN:
							switch(Event.button.button)
							{
								case SDL_BUTTON_LEFT:

									if (gc.isOpen()){

										gc.processMouseEvent(&Event);

									} else {

										switch(menu.btnHit())
										{
											case 0:
												Starting = false;
												Running = true;

												setupGame(&gm,&gc);

												gm.startGame();
												break;
											case 1:
												gc.start();
												break;
											case 2:
												Running = false;
												Starting = false;
												break;
											default:
												break;
										}
										break;
									}
							}
							break;
				}
				if (gc.isOpen())
					gc.update(renderer);
				else
					menu.show();
				SDL_RenderPresent(renderer);
			}
		}
	    while (Running) 
	    {

	    	if (fps.isFrameDone()) {

	    		SDL_RenderClear(renderer);

				while(SDL_PollEvent(&Event))
				{
					switch(Event.type)
					{
						case SDL_QUIT:
							Running = false;
							Starting = false;
							break;

						case SDL_KEYDOWN:
							switch(Event.key.keysym.sym)
							{
								case SDLK_ESCAPE:
									Running = false;
									break;
								case SDLK_BACKSPACE:
									Running = false;
									Starting = true;
									break;
								default:
									// GameManager.processEvent retorna true caso o programa deva fechar
									if (gm.processEvent(&Event)){
										Starting = false;
										Running = false;
									}
									break;
							}
							break;
						case SDL_MOUSEBUTTONDOWN:
							switch(Event.button.button)
							{
								case SDL_BUTTON_LEFT:
									SDL_GetMouseState(&x, &y);

									// GameManager.processMouseEvent retorna true caso o programa deva fechar
									if (gm.processMouseEvent(&Event)) {
										Starting = false;
										Running = false;
									}
									break;
							}
							break;
					}
				}

				//FPS BEGIN

				fps.plus();
				if (actual != hold)
				{
					fps.calculate();
					fps.setFrames(0);
					hold = fps.setEnd();

				}
				else
				{
					actual = fps.setEnd();
				}				
				//FPS END

				SDL_Rect uRect;
				gm.update(renderer,font,&uRect);

				fps.show(renderer,font);

				SDL_RenderPresent(renderer);
	    	}
	    }
	}

	SDL_Quit();
	return EXIT_SUCCESS;
}

