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

GameManager::GameManager(Board* newBoard, SDL_Renderer *r){
	turn = GAMEMANAGER_INITIAL_TURN;
	board = newBoard;
	teamABodyCount = 0;
	teamBBodyCount = 0;
	context = IDLE;
	activeSpell = 0;
	actionsPerTurn = 0;
	movesPerTurn = 0;
	renderer = r;
	context = IDLE;
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
//	do {
//		startTurn();
//	} while (teamABodyCount > 0 && teamBBodyCount > 0);
	turn = 0;
	startNextTurn();
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

	context = IDLE;

	cleanup();
}

void GameManager::notifyDeath(T_TEAM team, int casualties){
	if (team == TEAM_A) {
		teamABodyCount-=casualties;
	} else {
		teamBBodyCount-=casualties;
	}
}

T_ERROR GameManager::startNextTurn(){
	turn++;
	context = BEGINNING_TURN;
	std::cout << "Começando o turno " << turn << std::endl;

	// Sort do vetor de unidades, baseados na "speed" de cada unidade

	// Seta activeUnit como a primeira unidade da lista
	activeUnit = unitList.begin();

	T_ERROR e = startNextUnitTurn();
	if (e != T_SUCCESS) {
		// tratar erro
		return e;
	}

	return T_SUCCESS;
}

T_ERROR GameManager::endTurn(){
	std::cout << "Terminando o turno " << turn << std::endl;
	context = ENDING_TURN;
	// Verificar efeitos de fim de turno

	// Verificar se o jogo acabou
	if (teamABodyCount <= 0 || teamBBodyCount <= 0) {
		endGame();
		return T_SUCCESS;
	}

	return startNextTurn();
}

T_ERROR GameManager::startNextUnitTurn(){
	context = BEGINNING_UNIT_TURN;

	Unit *u = *activeUnit;
	actionsPerTurn = u->getActionsPerTurn();
	movesPerTurn = u->getMove();

	std::cout << "Iniciando turno da unidade: " << u << std::endl;
	u->debug_showStats(true);

	context = UNIT_MENU;

	// show menu

	//TODO: alterar aqui para exibi o menu na tela
	showUnitMenu();

	return T_SUCCESS;
}

T_ERROR GameManager::endUnitTurn(){
	context = ENDING_UNIT_TURN;
	// Verificar efeitos de fim de turno


	// Verificar se o jogo acabou
	if (teamABodyCount <= 0 || teamBBodyCount <= 0) {
		endGame();
		return T_SUCCESS;
	}

	// incrementar o iterador de unidades
	activeUnit++;

	// Se chegou ao fim da lista, terminar o turno
	if (activeUnit == unitList.end())
		return endTurn();

	// Começar o turno da proxima unidade
	return startNextUnitTurn();
}

void GameManager::processEvent(SDL_Event *event){
	SDL_Keycode key;
	if (event->type == SDL_KEYDOWN)
		key = event->key.keysym.sym;
	else
		return;

	switch(context){
		case IDLE:
			if (key == SDLK_s)
				startGame();
			break;
		case BEGINNING_TURN:

		case ENDING_TURN:

		case BEGINNING_UNIT_TURN:

		case ENDING_UNIT_TURN:

		case SPELL_EFFECT:

		case UNIT_MENU:
			switch(key){
				case SDLK_m:
					//Unidade não pode mais mover
					if (movesPerTurn <= 0)
						break;

					// move unit
					context = UNIT_MOVE;
					showMoveOptions();
					break;
				case SDLK_p:
					// fim do turno da unidade
					endUnitTurn();
					break;
				case SDLK_a:
					// Unidade nao pode mais atacar
					if (actionsPerTurn <= 0)
						break;

					// combate
					showAttackOptions();
					context = UNIT_SELECT_TARGET;
					break;
				case SDLK_s:
					// Unidade nao pode mais usar spells
					if (actionsPerTurn <= 0)
						break;

					// magias
					showSpellMenu();
					context = SPELL_MENU;
					break;
			}
			break;
		case SPELL_MENU:
			if (key == SDLK_0 || key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4 ||
				key == SDLK_5 || key == SDLK_6 || key == SDLK_7 || key == SDLK_8 || key == SDLK_9) {

					vector<Spell *> *spellList = (*activeUnit)->getSpellList();
					int index = key - '0' - 1;
					Spell* spell = spellList->at(index);

					// verificar se a spell é valida
					activeSpell = spell;

					showTargetOptions();
					context = SPELL_SELECT_TARGET;
			}
			break;

		case UNIT_COMBAT:

		case UNIT_MOVE:
			if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				moveUnit(key);

			board->debug_showMap();
			break;
		case UNIT_SELECT_TARGET:
			if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				selectCombatTarget(key);

			break;
		case SPELL_SELECT_TARGET:
			if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				selectSpellTargets(key);

			break;
	}
}

T_ERROR GameManager::moveUnit(SDL_Keycode direction){

	if (movesPerTurn <= 0) {
		std::cerr << "Unidade nao pode mais mover" << std::endl;
		context = UNIT_MENU;
		showUnitMenu();
		return T_ERROR_UNIT_OUT_OF_MOVES;
	}
	Unit *unit = *activeUnit;
	T_ERROR e;
	if (direction == SDLK_LEFT)
		e = board->moveUnit(unit,unit->getX()-1,unit->getY());
	else if (direction == SDLK_DOWN)
		e =board->moveUnit(unit,unit->getX(),unit->getY()-1);
	else if (direction== SDLK_RIGHT)
		e = board->moveUnit(unit,unit->getX()+1,unit->getY());
	else if (direction == SDLK_UP)
		e = board->moveUnit(unit,unit->getX(),unit->getY()+1);

	if (e == T_SUCCESS) {
		movesPerTurn--;
		showUnitMenu();
		context = UNIT_MENU;
	} else {
		std::cerr << "Posicao invalida" << std::endl;
		showMoveOptions();
	}

	return T_SUCCESS;
}

void GameManager::showMap(){
	board->debug_showMap();
}

void GameManager::showMap(TTF_Font *font){
	drawBoard(renderer,board);
}

void GameManager::showUnitMenu(){
	showMap();
	std::cout << "Pressione M para mover, A para atacar, S para utilizar uma magia, e P para pular" << std::endl;
}

void GameManager::showSpellMenu(){
	Unit * unit = *activeUnit;
	vector<Spell *> *spellList = unit->getSpellList();
	std::cout << "Pressione o numero correspondente da spell desejada:" << std::endl;
	for (std::vector<Spell *>::iterator it = spellList->begin(); it != spellList->end(); it++){
		Spell* spell = (*it);
		std::cout << "(" << it - spellList->begin() + 1 << "): " << spell->getName() << std::endl;
	}
}

void GameManager::showMoveOptions(){
	showMap();
	std::cout << "Utilize as setas para mover a unidade" << std::endl;
}

void GameManager::showAttackOptions(){
	showMap();
	std::cout << "Utilize as setas para selecionar um alvo" << std::endl;
}

void GameManager::showTargetOptions(){
	showMap();
	std::cout << "Utilize as setas para selecionar um alvo" << std::endl;
}

T_ERROR GameManager::selectCombatTarget(SDL_Keycode key){

	Unit *unit = *activeUnit;
	vector<Unit*> targets;
	T_ERROR e;

	switch(key){
		case SDLK_LEFT:
			e = board->checkUnitsInAOE(unit->getX()-1,unit->getY(),unit->getRange(),BOARD_AXIS_X_MINUS,unit->getAttackArea(),&targets);
			break;
		case SDLK_DOWN:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()-1,unit->getRange(),BOARD_AXIS_Y_MINUS,unit->getAttackArea(),&targets);
			break;
		case SDLK_RIGHT:
			e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),unit->getRange(),BOARD_AXIS_X,unit->getAttackArea(),&targets);
			break;
		case SDLK_UP:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()+1,unit->getRange(),BOARD_AXIS_Y,unit->getAttackArea(),&targets);
			break;
	}

	context = UNIT_COMBAT;

	if (e == T_SUCCESS)
		e = combat(&targets);
	else {
		std::cout << "Alvo invalido" << std::endl;
		showAttackOptions();
	}
	return T_SUCCESS;
}

T_ERROR GameManager::selectSpellTargets(SDL_Keycode key){
	Unit* unit = *activeUnit;
	vector<Unit*> targets;
	T_ERROR e;
	switch(key) {
		case SDLK_LEFT:
			e = board->checkUnitsInAOE(unit->getX()-1,unit->getY(),activeSpell->getRange(),BOARD_AXIS_X_MINUS,activeSpell->getAreaOfEffect(),&targets);
			break;
		case SDLK_DOWN:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()-1,activeSpell->getRange(),BOARD_AXIS_Y_MINUS,activeSpell->getAreaOfEffect(),&targets);
			break;
		case SDLK_RIGHT:
			e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),activeSpell->getRange(),BOARD_AXIS_X,activeSpell->getAreaOfEffect(),&targets);
			break;
		case SDLK_UP:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()+1,activeSpell->getRange(),BOARD_AXIS_Y,activeSpell->getAreaOfEffect(),&targets);
			break;
	}

	if (e == T_SUCCESS) {
		context = SPELL_EFFECT;
		e = useSpell(&targets);
	}

	return T_SUCCESS;
}

T_ERROR GameManager::combat(vector<Unit*> *targets){
	Unit* unit = *activeUnit;
	T_ERROR e;
	if (unit->getTeam() == TEAM_A)
		e = unit->combat(targets,&teamBBodyCount);
	else
		e = unit->combat(targets,&teamABodyCount);

	if (e == T_SUCCESS)
		actionsPerTurn--;

	if (teamABodyCount <= 0 || teamBBodyCount <= 0){
		endGame();
		return T_SUCCESS;
	}

	context = UNIT_MENU;
	showUnitMenu();
	return T_SUCCESS;
}

T_ERROR GameManager::useSpell(vector<Unit*> *targets){
	Unit* unit = *activeUnit;

	std::cout << "Vetor vazio? " << targets->empty() << std::endl;
	for (std::vector<Unit*>::iterator it=targets->begin(); it != targets->end(); it++) {
		std::cout << "unidade: " << *it << std::endl;
		(*it)->debug_showStats();
	}

	T_ERROR e = activeSpell->perform(this, targets);
	if (e == T_SUCCESS){
		actionsPerTurn--;
		if (getOtherTeamBodyCount(unit->getTeam()) == 0){
			endGame();
			return T_SUCCESS;
		}
	} else {
		std::cerr << "Erro ao usar a spell " << activeSpell << " e=" << e << std::endl;
	}

	context = UNIT_MENU;
	showUnitMenu();

	return T_SUCCESS;
}

void GameManager::update(SDL_Renderer* r,TTF_Font *font){
//	showMap(font);
	std::cout << "GameManager::update!" << std::endl;
	for (std::vector<Unit*>::iterator it=unitList.begin(); it != unitList.end(); it++)
		showUnit(*it,r,font);
}

void GameManager::showUnit(Unit* unit,SDL_Renderer *r, TTF_Font* font){
	drawUnit(unit,r,font);
}
