/*
 * GameManager.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "GameManager.h"
#include <typeinfo>

GameManager::GameManager(Board* newBoard){
	turn = GAMEMANAGER_INITIAL_TURN;
	board = newBoard;
}

GameManager::~GameManager(){
	for (std::vector<Unit *>::iterator unit = unitList.begin(); unit != unitList.end(); unit++) {
			delete (*unit);
	}
}

void GameManager::createUnit(string unitClass, T_TEAM team){
	std::cout << "GameManager::createUnit class= " << unitClass << std::endl;

	if (unitClass == "knight") {
		std::cout << "Creating new knight" << std::endl;
		Knight* newUnit = new Knight(team);
		std::cout << "Criou knight: typeid=" << typeid(newUnit).name() << std::endl;
		unitList.push_back(newUnit);
		board->addUnit(newUnit);
		std::cout << "New Unit (x,y) = (" << newUnit->getX() << "," << newUnit->getY() << ")" << std::endl;
	} else if (unitClass == "wizard") {
		std::cout << "Creating new wizard" << std::endl;
		Wizard* newUnit = new Wizard(team);
		unitList.push_back(newUnit);
		board->addUnit(newUnit);
		std::cout << "New Unit (x,y) = (" << newUnit->getX() << "," << newUnit->getY() << ")" << std::endl;
	}


}


void GameManager::startGame(){
	std::cout << "GameManager::startGame()" << std::endl;
	board->debug_showMap();
	startTurn();
	board->debug_showMap();
}

void  GameManager::startTurn(){
	turn++;

	for (std::vector<Unit *>::iterator unit = unitList.begin(); unit != unitList.end(); unit++) {
		int movePerTurn = (*unit)->getMove();
		int actionPerTurn = 0;
				//(*unit)->getActionsPerTurn();
		bool endUnitTurn = false;

		while (endUnitTurn == false ) {
			char input;
			if (movePerTurn > 0 || actionPerTurn > 0) {
				board->debug_showMap();
				std::cout << "Pressione M para mover, e A para atacar" << std::endl;
				std::cin >> input;
				if (input == 'a') {
					// Tratar combate
				} else if (input == 'm') {
					std::cout << "Pressione W, A, S, D para mover" << std::endl;
					board->debug_showMap();
					std::cin >> input;
					T_ERROR e;

					if (input == 'w') {
						e = board->moveUnit(*unit,(*unit)->getX(),(*unit)->getY()+1);
					} else if (input == 'a') {
						e = board->moveUnit(*unit,(*unit)->getX()-1,(*unit)->getY());
					} else if (input == 's') {
						e = board->moveUnit(*unit,(*unit)->getX(),(*unit)->getY()-1);
					} else if (input == 'd') {
						e = board->moveUnit(*unit,(*unit)->getX()+1,(*unit)->getY());
					}

					if (e == T_SUCCESS) {
						board->debug_showMap();
						movePerTurn--;
					} else {
						std::cout << "Posicao invalida!" << std::endl;
					}
				}

			} else {
				std::cout << "Pressione alguma tecla para terminar turno..." << std::endl;
				std::cin >> input;
				endUnitTurn = true;
			}
		}

	}

}
