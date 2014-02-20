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

using namespace std;

int main(int argc, char *argv[]){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480,
		SDL_WINDOW_SHOWN);
	if (win == 0){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::cin.get();

//	std::cout << "Iniciando jogo Tactics!" << std::endl;
//
//	std::cout << "Criando tabuleiro!" << std::endl;
//	Board gameBoard(8,8);
//
//	std::cout << "Criando GameManager!" << std::endl;
//	GameManager gm(&gameBoard);
//
//	std::cout << "Criando unidade 1!" << std::endl;
//	gm.createUnit("knight",TEAM_A);
//
//	std::cout << "Criando unidade 2!" << std::endl;
//	gm.createUnit("wizard",TEAM_A);
//
//	gameBoard.debug_showMap();
//
//	gm.startGame();








//	SDL_Quit();
	return 0;
}

