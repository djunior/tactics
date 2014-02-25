/*
 * GameManager.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "gameManager.h"
#include <typeinfo>
#include "unit_class/Knight.h"
#include "unit_class/Wizard.h"

GameManager::GameManager(Board* newBoard){
	turn = GAMEMANAGER_INITIAL_TURN;
	board = newBoard;
	teamABodyCount = 0;
	teamBBodyCount = 0;
}

GameManager::~GameManager(){
	cleanup();
}

void GameManager::cleanup(){
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

	if (team == TEAM_A)
		teamABodyCount++;
	else
		teamBBodyCount++;
}


void GameManager::startGame(){
	std::cout << "GameManager::startGame()" << std::endl;
	board->debug_showMap();
	do {
		startTurn();
	} while (teamABodyCount > 0 && teamBBodyCount > 0);
	endGame();
}

void  GameManager::startTurn(){
	turn++;
	bool forceEnd = false;
	for (std::vector<Unit *>::iterator it = unitList.begin(); it != unitList.end(); it++) {
		Unit *unit = (*it);
		if (forceEnd == false && !unit->isDead()) {
			std::cout << "Iniciando turno da unidade: " << unit << std::endl;
			unit->debug_showStats();
			int movePerTurn = unit->getMove();
			int actionPerTurn = unit->getActionsPerTurn();
			bool endUnitTurn = false;
			while (forceEnd == false && endUnitTurn == false ) {
				char input;
				if (movePerTurn > 0 || actionPerTurn > 0) {
					board->debug_showMap();
					std::cout << "Pressione M para mover, A para atacar, S para utilizar uma magia, e P para pular" << std::endl;
					std::cin >> input;
					if (input == 'a' && actionPerTurn > 0) {

						vector<Unit *> targets;
						T_ERROR e;
						// Tratar combate
						std::cout << "Pressione W, A, S, D para selecionar o alvo" << std::endl;
						board->debug_showMap();
						std::cin >> input;

						if (input == 'w')
							e = board->checkUnitsInAOE(unit->getX()-1,unit->getY(),unit->getRange(),BOARD_AXIS_X_MINUS,unit->getAttackArea(),&targets);
						else if (input == 'a')
							e = board->checkUnitsInAOE(unit->getX(),unit->getY()-1,unit->getRange(),BOARD_AXIS_Y_MINUS,unit->getAttackArea(),&targets);
						else if (input == 's')
							e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),unit->getRange(),BOARD_AXIS_X,unit->getAttackArea(),&targets);
						else if (input == 'd')
							e = board->checkUnitsInAOE(unit->getX(),unit->getY()+1,unit->getRange(),BOARD_AXIS_X,unit->getAttackArea(),&targets);

						if (e == T_SUCCESS) {
							if (unit->getTeam() == TEAM_A)
								e = unit->combat(&targets,&teamBBodyCount);
							else
								e = unit->combat(&targets,&teamABodyCount);
						} else {
							std::cout << "Alvo invalido!" << std::endl;
						}

						if (e == T_SUCCESS) {
							actionPerTurn--;

							if (getOtherTeamBodyCount(unit->getTeam()) == 0){
								std::cout << "O outro time todo morreu" << std::endl;
								forceEnd = true;
							}
						}
					} else if (input == 's' && actionPerTurn > 0) {
						vector<Spell *> *spellList = unit->getSpellList();
						std::cout << "Pressione o numero correspondente da spell desejada:" << std::endl;
						for (std::vector<Spell *>::iterator it = spellList->begin(); it != spellList->end(); it++){
							Spell* spell = (*it);
							std::cout << "(" << it - spellList->begin() + 1 << "): " << spell->getName() << std::endl;
						}
						Spell *spell = 0;
						std::cin >> input;
						int index = input - '0' - 1;
						std::cout << "INPUT=" << input << " INDEX =" << index << std::endl;
						if (input == '1') {
							 spell = spellList->at(index);
						}
						T_ERROR e;
						vector<Unit *> targets;
						if (spell != 0) {
							std::cout << "Pressione W, A, S, D para selecionar o alvo" << std::endl;
							board->debug_showMap();
							std::cin >> input;

							if (input == 'w')
								e = board->checkUnitsInAOE(unit->getX()-1,unit->getY(),spell->getRange(),BOARD_AXIS_X_MINUS,spell->getAreaOfEffect(),&targets);
							else if (input == 'a')
								e = board->checkUnitsInAOE(unit->getX(),unit->getY()-1,spell->getRange(),BOARD_AXIS_Y_MINUS,spell->getAreaOfEffect(),&targets);
							else if (input == 's')
								e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),spell->getRange(),BOARD_AXIS_X,spell->getAreaOfEffect(),&targets);
							else if (input == 'd')
								e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),spell->getRange(),BOARD_AXIS_X,spell->getAreaOfEffect(),&targets);

							if (e == T_SUCCESS) {
								if (spell->perform(this, &targets) == T_SUCCESS){
									actionPerTurn--;
									if (getOtherTeamBodyCount(unit->getTeam()) == 0){
										std::cout << "Um time morreu. Escapando turno..." << std::endl;
										forceEnd = true;
									}
								}
							}
						}
					} else if (input == 'm' && movePerTurn > 0) {
						std::cout << "Pressione W, A, S, D para mover" << std::endl;
						board->debug_showMap();
						std::cin >> input;
						T_ERROR e;

						if (input == 'w')
							e = board->moveUnit(unit,unit->getX()-1,unit->getY());
						else if (input == 'a')
							e = board->moveUnit(unit,unit->getX(),unit->getY()-1);
						else if (input == 's')
							e = board->moveUnit(unit,unit->getX()+1,unit->getY());
						else if (input == 'd')
							e = board->moveUnit(unit,unit->getX(),unit->getY()+1);

						if (e == T_SUCCESS) {
							board->debug_showMap();
							movePerTurn--;
						} else {
							std::cout << "Posicao invalida!" << std::endl;
						}
					}	else if (input == 'p') {
						endUnitTurn = true;
					}

				} else {
					endUnitTurn = true;
				}
			}
		}

		if (teamABodyCount == 0 || teamBBodyCount == 0){
			forceEnd = true;
		}
	}
	std::cout << "Fim do turno " << turn << std::endl;
}

int GameManager::getOtherTeamBodyCount(T_TEAM team) {
	if (team == TEAM_A)
		return teamBBodyCount;
	else
		return teamABodyCount;
}

void GameManager::endGame(){
	if (teamABodyCount == 0)
		std::cout << "Time B venceu no turno " << turn << std::endl;
	else if (teamBBodyCount == 0)
		std::cout << "Time A venceu no turno " << turn << std::endl;

	cleanup();
}

void GameManager::notifyDeath(T_TEAM team, int casualties){
	if (team == TEAM_A) {
		teamABodyCount-=casualties;
	} else {
		teamBBodyCount-=casualties;
	}
}
