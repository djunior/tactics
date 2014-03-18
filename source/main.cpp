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
#include "unit.h"

#include "drawFunctions.h"

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
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	SDL_SetWindowMinimumSize(window,min_wWindow,min_hWindow);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL){
        cout << SDL_GetError() << endl;
        return 1;
    }

    Screen::init(renderer, window);

    Board gameBoard(8,4);
    GameManager gm(&gameBoard, renderer);

    
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
    cerr << "Criando unidade 1!" << endl;
    gm.createUnit("wizard",TEAM_A);

    cerr << "Criando unidade 2!" << endl;
    gm.createUnit("wizard",TEAM_B);

//    cerr << "Criando unidade 3!" << endl;
//    gm.createUnit("knight",TEAM_A);
//
//    cerr << "Criando unidade 4!" << endl;
//    gm.createUnit("knight",TEAM_B);

    gameBoard.debug_showMap();
    // Unit create END

    menu.mainMenu();

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
									switch(menu.btnHit())
									{
										case 0:
											Starting = false;
											Running = true;
											gm.startGame();
											break;
										case 1:
											Running = false;
											Starting = false;
											break;
										default:
											break;
									}
									break;
							}
							break;
				}
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
									gm.processEvent(&Event);
							}
							break;
						case SDL_MOUSEBUTTONDOWN:
							switch(Event.button.button)
							{
								case SDL_BUTTON_LEFT:
									SDL_GetMouseState(&x, &y);
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

