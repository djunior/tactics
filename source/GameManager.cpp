/*
 * GameManager.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */


#include "GameManager.h"

GameManager::GameManager(Board* newBoard){
	turn = GAMEMANAGER_INITIAL_TURN;
	board = newBoard;
}

void GameManager::createUnit(string unitClass, T_TEAM team){
	std::cout << "GameManager::createUnit" << std::endl;
	Unit* newUnit = new Unit(team);
	std::cout << "GameManager::createUnit pushing back unit" << std::endl;
	unitList.push_back(newUnit);
	std::cout << "GameManager::createUnit adding unit to the board" << std::endl;
	board->addUnit(newUnit);

	std::cout << "New Unit (x,y) = (" << newUnit->getX() << "," << newUnit->getY() << ")" << std::endl;
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
		// Do stuff that affect the unit
		std::cout << "Varrendo lista de unidades: " << (unit-unitList.begin()) << std::endl;
		std::cout << "Unidade: " << (*unit) << std::endl;
		std::cout << "Movendo unidade de (" << (*unit)->getX() << "," << (*unit)->getY() << ") para: (" << (*unit)->getX() << "," << ((*unit)->getY()+1) << ")" << std::endl;

		T_ERROR e = board->moveUnit(*unit,(*unit)->getX(),(*unit)->getY()+1);

		std::cout << "Error: " << e << std::endl;
	}

}
