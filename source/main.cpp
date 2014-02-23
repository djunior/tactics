/*
 * main.c
 *
 *	Projeto Tactics
 *
 *  Created on: Feb 12, 2014
 *      Author: djunior
 */
#include <iostream>
#include <stdio.h>

#include "Board.h"
#include "GameManager.h"
#include "Unit.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

int main(int argc, char *argv[]){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

    bool Running = true;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event Event;

    SDL_Texture *Track,*Car;
    SDL_Rect rectTrack,rectCar;

    // OnInit

    window = SDL_CreateWindow("Image Loading", 100, 100, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC);
	if (window == 0){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //Load Content
    int w=0,h=0;
    Track = IMG_LoadTexture(renderer,"images\\mapa.jpg");
    SDL_QueryTexture(Track, NULL, NULL, &w, &h);
    rectTrack.x = 0;
    rectTrack.y = 0;
    rectTrack.w = w;
    rectTrack.h = h;

    Car = IMG_LoadTexture(renderer, "images\\char_lanca.png");
    SDL_QueryTexture(Car, NULL, NULL, &w, &h);
    rectCar.x = 350;
    rectCar.y = 200;
    rectCar.w = w/2;
    rectCar.h = h;

    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=w/4;
    src.h=h/2;

    while (Running) {
        while(SDL_PollEvent(&Event)) {
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
							rectCar.x+=10;
							break;
						case SDLK_LEFT:
							rectCar.x-=10;
							break;
					}
					break;

			}
        }

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Track, NULL, &rectTrack);
		SDL_RenderCopy(renderer, Car, &src, &rectCar);
		SDL_RenderPresent(renderer);
    }

	SDL_Quit();
	return 0;
}

