/*
 * main.c
 *
 *	Projeto Tactics
 *
 *  Created on: Feb 12, 2014
 *      Author: djunior
 */
#include "basic_includes.h"

#include "animation.h"
#include "fpsControl.h"

#include "board.h"
#include "gameManager.h"
#include "unit.h"
#include "drawFunctions.h"

int main(int argc, char *argv[]){

    sdlInit();
    textInit();

    bool Running = true;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event Event;

    SDL_Texture *Map,*Char;
    SDL_Rect rectMap,rectChar;

    TTF_Font *font;
    SDL_Texture *tTexture;
    SDL_Rect rectText;

    framesPerSecond fps;

    // OnInit

    window = SDL_CreateWindow("Tactics", 100, 100, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC);
	if (window == 0){
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL){
        cout << SDL_GetError() << endl;
        return 1;
    }

    Screen::init(renderer);

    Board gameBoard(3,3);
    GameManager gm(&gameBoard, renderer);

    //Load Content
    int w=0,h=0;
    Map = IMG_LoadTexture(renderer,"images\\mapa.jpg");
    SDL_QueryTexture(Map, NULL, NULL, &w, &h);
    rectMap.x = 0;
    rectMap.y = 0;
    rectMap.w = w;
    rectMap.h = h;

    Char = IMG_LoadTexture(renderer, "images\\char_lanca.png");
    SDL_QueryTexture(Char, NULL, NULL, &w, &h);
    rectChar.x = 350;
    rectChar.y = 200;
    rectChar.w = w/2;
    rectChar.h = h;

    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=w/4;
    src.h=h/2;
    
    // FPS Setup BEGIN

    font = loadFont();  

    fps.setFrames(0);
    time_t hold;
    time_t actual;
    hold = fps.start();
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
    //gm.startGame();

    // Unit create END

    FpsControl fpsControl(60);

    gm.startGame();
    while (Running) 
    {
    	if (fpsControl.isFrameDone()) {

    		SDL_RenderClear(renderer);

    		while(SDL_PollEvent(&Event))
			{
				switch(Event.type)
				{
					case SDL_QUIT:
						Running = false;
						break;

					case SDL_KEYDOWN:
						switch(Event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								Running = false;
								break;
							default:
								gm.processEvent(&Event);
						}
						break;

				}
			}

//			SDL_RenderCopy(renderer, Map, NULL, &rectMap);
//			SDL_RenderCopy(renderer, Char, &src, &rectChar);
//
//			//FPS BEGIN
//
			fps.plus();
			if (actual != hold)
			{
				fps.calculate();
				fps.setFrames(0);
				hold = fps.end();

			}
			else
			{
				actual = fps.end();
			}
			tTexture = fps.show(renderer,font);
			rectText = fps.getRect();
			SDL_RenderCopy(renderer, tTexture, NULL, &rectText);

			//FPS END
			SDL_Rect uRect;
			gm.update(renderer,font,&uRect);

			//SDL_RenderCopy(renderer,texture,NULL,&uRect);
			SDL_RenderPresent(renderer);
    	}
    }

	SDL_Quit();
	return EXIT_SUCCESS;
}

