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

	return 0;
}

