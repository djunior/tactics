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

