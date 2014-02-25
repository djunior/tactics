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

#include "Board.h"
#include "GameManager.h"
#include "Unit.h"

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
    Board gameBoard(8,8);
    GameManager gm(&gameBoard);


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

    //gameBoard.debug_showMap();
    //gm.startGame();

    // Unit create END

    while (Running) 
    {
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
						case SDLK_RIGHT:
							rectChar.x+=10;
							break;
						case SDLK_LEFT:
							rectChar.x-=10;
							break;
					}
					break;

			}
        }

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Map, NULL, &rectMap);
		SDL_RenderCopy(renderer, Char, &src, &rectChar);

        //FPS BEGIN

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

		SDL_RenderPresent(renderer);
    }

	SDL_Quit();
	return EXIT_SUCCESS;
}

