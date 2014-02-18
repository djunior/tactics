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

using namespace std;

int main(){
	cout << "Iniciando jogo Tactics!" << endl;

	cout << "Criando tabuleiro!" << endl;
	Board gameBoard(8,8);

	cout << "Criando GameManager!" << endl;
	GameManager gm(&gameBoard);

	cout << "Criando unidade 1!" << endl;
	gm.createUnit("knight",TEAM_A);

	cout << "Criando unidade 2!" << endl;
	gm.createUnit("wizard",TEAM_A);

	gameBoard.debug_showMap();

	gm.startGame();

	return 0;
}

