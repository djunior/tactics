/*
 * GameManager.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "gameManager.h"
#include <typeinfo>
#include "unit_class/knight.h"
#include "unit_class/wizard.h"

GameManager::GameManager(Board* newBoard, SDL_Renderer *r, SDL_Window *w){
	turn = GAMEMANAGER_INITIAL_TURN;
	board = newBoard;
	teamABodyCount = 0;
	teamBBodyCount = 0;
	context = CONTEXT_IDLE;
//	activeSpell = 0;
	actionsPerTurn = 0;
	movesPerTurn = 0;
	renderer = r;
	window = w;
	winningTeam = TEAM_A;

	menu.setup(r,w,MENU_END_GAME);

	menuUnitAction.setup(r,w,MENU_UNIT_ACTION);
	menuUnitAction.unitActionMenu(-100,350);
}

GameManager::~GameManager(){
	cleanup();
}

void GameManager::cleanup(){
	for (std::vector<Unit *>::iterator unit = unitList.begin(); unit != unitList.end(); unit++) {
		delete (*unit);
	}
}

void GameManager::createUnit(UNIT_CLASS unitClass, T_TEAM team){

	if (unitClass == UNIT_CLASS_KNIGHT) {
		Knight* newUnit = new Knight(team,renderer,window);
		unitList.push_back(newUnit);
		board->addUnit(newUnit);
	} else if (unitClass == UNIT_CLASS_WIZARD) {
		Wizard* newUnit = new Wizard(team,renderer,window);
		unitList.push_back(newUnit);
		board->addUnit(newUnit);
	}

	if (team == TEAM_A)
		teamABodyCount++;
	else
		teamBBodyCount++;
}


void GameManager::startGame(){
	turn = 0;
	startNextTurn();
}

//Deprecated
void  GameManager::startTurn(){
	turn++;
	bool forceEnd = false;
	for (std::vector<Unit *>::iterator it = unitList.begin(); it != unitList.end(); it++) {
		Unit *unit = (*it);
		if (forceEnd == false && !unit->isDead()) {
			int movePerTurn = unit->getMove();
			int actionPerTurn = unit->getActionsPerTurn();
			bool endUnitTurn = false;
			while (forceEnd == false && endUnitTurn == false ) {
				char input;
				if (movePerTurn > 0 || actionPerTurn > 0) {
					std::cin >> input;
					if (input == 'a' && actionPerTurn > 0) {

						vector<Unit *> targets;
						T_ERROR e;
						// Tratar combate
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
							// Cuidar de erros
						}

						if (e == T_SUCCESS) {
							actionPerTurn--;

							if (getOtherTeamBodyCount(unit->getTeam()) == 0){
								forceEnd = true;
							}
						}
					} else if (input == 's' && actionPerTurn > 0) {
						/*
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
					*/
					} else if (input == 'm' && movePerTurn > 0) {
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
							movePerTurn--;
						} else {
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
}

int GameManager::getOtherTeamBodyCount(T_TEAM team) {
	if (team == TEAM_A)
		return teamBBodyCount;
	else
		return teamABodyCount;
}

void GameManager::endGame(){
	if (teamABodyCount == 0)
		winningTeam = TEAM_B;
	else if (teamBBodyCount == 0)
		winningTeam = TEAM_A;

	context = CONTEXT_END_GAME;

	menu.endMenu(winningTeam,turn);
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
	context = CONTEXT_BEGINNING_TURN;

	// TODO: adicionar algoritmo de sort
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
	context = CONTEXT_ENDING_TURN;

	// TODO: Verificar efeitos de fim de turno

	// Verificar se o jogo acabou
	if (teamABodyCount <= 0 || teamBBodyCount <= 0) {
		endGame();
		return T_SUCCESS;
	}

	return startNextTurn();
}

T_ERROR GameManager::startNextUnitTurn(){
	context = CONTEXT_BEGINNING_UNIT_TURN;

	Unit *u = *activeUnit;

	if (u->isDead()){
		endUnitTurn();
		return T_SUCCESS;
	}

	actionsPerTurn = u->getActionsPerTurn();
	movesPerTurn = u->getMove();

	context = CONTEXT_UNIT_MENU;

	// show menu

	//TODO: alterar aqui para exibi o menu na tela
	//showUnitMenu();

	return T_SUCCESS;
}

T_ERROR GameManager::endUnitTurn(){
	context = CONTEXT_ENDING_UNIT_TURN;
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

	// Come�ar o turno da proxima unidade
	return startNextUnitTurn();
}

bool GameManager::processMouseEvent(SDL_Event *event){
	if (! event->type == SDL_MOUSEBUTTONDOWN)
		return false;

	if (! event->button.button == SDL_BUTTON_LEFT)
		return false;
	bool close = false;
	switch(context){
		case CONTEXT_UNIT_MENU:
			switch(menuUnitAction.btnHit())
			{
				case 0:
					//Unidade n�o pode mais mover
					if (movesPerTurn <= 0)
						break;

					// move unit
					context = CONTEXT_UNIT_SELECT_MOVE;
					showMoveOptions();
					break;
				case 1:
					// Unidade nao pode mais atacar
					if (actionsPerTurn <= 0)
						break;

					// combate
					showAttackOptions();
					context = CONTEXT_UNIT_SELECT_TARGET;
					break;
				case 2:
					// fim do turno da unidade
					endUnitTurn();
					break;
			}
			break;
		case CONTEXT_UNIT_SELECT_MOVE:
			moveUnit();
			break;
		case CONTEXT_UNIT_SELECT_TARGET:
			selectCombatTarget();
			break;
		case CONTEXT_END_GAME:
			switch(menu.btnHit()) 	{
				case 0:
				case 1:
					close = true;
					break;
			};
			break;
	}

	return close;
}

bool GameManager::processEvent(SDL_Event *event){
	SDL_Keycode key;
	if (event->type == SDL_KEYDOWN)
		key = event->key.keysym.sym;
	else
		return false;

	switch(context){
		case CONTEXT_IDLE:
			if (key == SDLK_s)
				startGame();
			break;
		case CONTEXT_BEGINNING_TURN:

		case CONTEXT_ENDING_TURN:

		case CONTEXT_BEGINNING_UNIT_TURN:

		case CONTEXT_ENDING_UNIT_TURN:

		case CONTEXT_SPELL_EFFECT:

		case CONTEXT_UNIT_MENU:
			switch(key){
				case SDLK_m:
					//Unidade n�o pode mais mover
					if (movesPerTurn <= 0)
						break;

					// move unit
					context = CONTEXT_UNIT_SELECT_MOVE;
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
					context = CONTEXT_UNIT_SELECT_TARGET;
					break;
				case SDLK_s:
					// Unidade nao pode mais usar spells
					if (actionsPerTurn <= 0)
						break;

					// magias
					showSpellMenu();
					context = CONTEXT_SPELL_MENU;
					break;
			}
			break;
		case CONTEXT_SPELL_MENU:
			if (key == SDLK_0 || key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4 ||
				key == SDLK_5 || key == SDLK_6 || key == SDLK_7 || key == SDLK_8 || key == SDLK_9) {
/*
					vector<Spell *> *spellList = (*activeUnit)->getSpellList();
					int index = key - '0' - 1;
					Spell* spell = spellList->at(index);

					// verificar se a spell � valida
					activeSpell = spell;

					showTargetOptions();
					context = CONTEXT_SPELL_SELECT_TARGET;
*/
			}
			break;

		case CONTEXT_UNIT_COMBAT:

		case CONTEXT_UNIT_SELECT_MOVE:
			if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				moveUnit(key);

			break;
		case CONTEXT_UNIT_SELECT_TARGET:
			if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				selectCombatTarget(key);

			break;
		case CONTEXT_SPELL_SELECT_TARGET:
			if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				selectSpellTargets(key);

			break;
	}

	return false;
}

T_ERROR GameManager::moveUnit(SDL_Keycode direction){

	if (movesPerTurn <= 0) {
		context = CONTEXT_UNIT_MENU;
		showUnitMenu();
		return T_ERROR_UNIT_OUT_OF_MOVES;
	}
	Unit *unit = *activeUnit;

	BOARD_POINT start;
	start.x = unit->getX();
	start.y = unit->getY();

	int x = unit->getX();
	int y = unit->getY();

	if (direction == SDLK_LEFT)
		x--;
	else if (direction == SDLK_DOWN)
		y++;
	else if (direction== SDLK_RIGHT)
		x++;
	else if (direction == SDLK_UP)
		y--;

	T_ERROR e = board->moveUnit(unit,x,y);

	if (e == T_SUCCESS) {
		movesPerTurn--;

		BOARD_POINT end;
		end.x = x;
		end.y = y;

		Animation a(ANIMATION_UNIT_MOVE,start,end,36,6,unit->getFramesAnimation(ANIMATION_UNIT_MOVE));
		unit->setAnimation(a);

		context = CONTEXT_UNIT_MOVE;
	} else {
		showMoveOptions();
	}

	return T_SUCCESS;
}

T_ERROR GameManager::moveUnit(){

	if (movesPerTurn <= 0) {
		context = CONTEXT_UNIT_MENU;
		showUnitMenu();
		return T_ERROR_UNIT_OUT_OF_MOVES;
	}
	Unit *unit = *activeUnit;

	T_ERROR e;

	BOARD_POINT start;
	start.x = unit->getX();
	start.y = unit->getY();

	BOARD_POINT end = start;

	int x = unit->getX();
	int y = unit->getY();
	int tryMoves;

	BOARD_AOE area;
	e = Screen::mouseBoardPosition(board,&area);

	if (e == T_SUCCESS){
		BOARD_POINT mouse;
		mouse.x = area.x;
		mouse.y = area.y;
		x -= mouse.x;
		y -= mouse.y;

		if(x<0) {
			x *= -1;
		}
		if(y<0)
			y *= -1;

		tryMoves = x+y;

		if(tryMoves > movesPerTurn) {
			context = CONTEXT_UNIT_MENU;
			showUnitMenu();
			return T_ERROR_UNIT_OUT_OF_MOVES;
		}
		x = unit->getX();
		y = unit->getY();
		x -= mouse.x;
		y -= mouse.y;
	}
	else {
		showMoveOptions();
		return e;
	}

	//board->moveUnit(unit,)

	e = board->moveUnit(unit,start.x-x,start.y-y);
	if (e == T_SUCCESS) {
		movesPerTurn-=tryMoves;
		end.x -= x;
		end.y -= y;

		int durationScale = ( ( abs(end.x - start.x) )^2 + ( abs(end.y - start.y) )^2 )^(1/2);
		if (durationScale < 1)
			durationScale = 1;

		Animation a(ANIMATION_UNIT_MOVE,start,end,36 * durationScale,6,unit->getFramesAnimation(ANIMATION_UNIT_MOVE));
		unit->setAnimation(a);
	}

	context = CONTEXT_UNIT_MOVE;
	return T_SUCCESS;
}

void GameManager::showMap(){
//	board->debug_showMap();
}

void GameManager::showMap(SDL_Renderer* r){
	Screen::drawBoard(renderer,board);
}

void GameManager::showUnitMenu(){
	Unit *unit = *activeUnit;
	unit->statsUpdate();
	unit->menu.show();

	stringstream ss;
	ss << movesPerTurn;
	(*activeUnit)->menu.textList[TEXTLIST_MOVE].setText("Move: " + ss.str());

	if (movesPerTurn > 0)
		menuUnitAction.enableButton(0);
	else
		menuUnitAction.disableButton(0);

	if (actionsPerTurn > 0)
		menuUnitAction.enableButton(1);
	else
		menuUnitAction.disableButton(1);

	menuUnitAction.show();
}

void GameManager::showSpellMenu(){
	/*
	Unit * unit = *activeUnit;
	vector<Spell *> *spellList = unit->getSpellList();
	std::cout << "Pressione o numero correspondente da spell desejada:" << std::endl;
	for (std::vector<Spell *>::iterator it = spellList->begin(); it != spellList->end(); it++){
		Spell* spell = (*it);
		std::cout << "(" << it - spellList->begin() + 1 << "): " << spell->getName() << std::endl;
	}
	*/
}

void GameManager::showMoveOptions(){
	showMap();
}

void GameManager::showAttackOptions(){
	showMap();
}

void GameManager::showTargetOptions(){
	showMap();
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
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()+1,unit->getRange(),BOARD_AXIS_Y,unit->getAttackArea(),&targets);
			break;
		case SDLK_RIGHT:
			e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),unit->getRange(),BOARD_AXIS_X,unit->getAttackArea(),&targets);
			break;
		case SDLK_UP:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()-1,unit->getRange(),BOARD_AXIS_Y_MINUS,unit->getAttackArea(),&targets);
			break;
	}

	context = CONTEXT_UNIT_COMBAT;

	if (e == T_SUCCESS)
		e = combat(&targets);
	else {
		showAttackOptions();
	}
	return T_SUCCESS;
}

T_ERROR GameManager::selectCombatTarget(){

	Unit *unit = *activeUnit;
	vector<Unit*> targets;
	vector<Unit*> possibleTargets;
	BOARD_AOE area;
	T_ERROR	e = Screen::mouseBoardPosition(board,&area);

	if (! e == T_SUCCESS){
		showAttackOptions();
		context = CONTEXT_UNIT_MENU;
		return e;
	}

	int x = unit->getX() - area.x;
	int y = unit->getY() - area.y;


	e = board->checkUnitsInAOE(unit->getX()-x,unit->getY()-y,0,BOARD_AXIS_X,AOE_SHAPE_POINT,&targets);
	if (! e == T_SUCCESS){
		//Nao selecionou nenhuma unidade com o clique
		showAttackOptions();
		context = CONTEXT_UNIT_MENU;
		return e;
	}

	context = CONTEXT_UNIT_COMBAT;
	e = board->checkUnitsInAOE(unit->getX(),unit->getY(),unit->getRange(),BOARD_AXIS_X,AOE_SHAPE_CROSS,&possibleTargets);

	if (e == T_SUCCESS) {
		//Esse loop pega todas as unidades dentro do AOE da unidade atacante,
		//e verifica se a unidade selecionada com o mouse esta dentro dessa area
		for (vector<Unit*>::iterator it=possibleTargets.begin(); it != possibleTargets.end(); it++){
			if ((*it) == targets.front()){
				e = combat(&targets);
				if ( e == T_SUCCESS) {
//					BOARD_POINT point;
//					point.x = unit->getX();
//					point.y = unit->getY();
//
//					Animation a(ANIMATION_UNIT_ATTACK,point,point,36,6);
//					unit->setAnimation(a);
				} else {
					context = CONTEXT_UNIT_MENU;
				}
				return e;
			}
		}
		//TODO: Fazer alguma coisa com o erro
	} else {
		context = CONTEXT_UNIT_MENU;
	}

	return T_SUCCESS;
}

T_ERROR GameManager::selectSpellTargets(SDL_Keycode key){
	Unit* unit = *activeUnit;
	vector<Unit*> targets;
	T_ERROR e;
	switch(key) {
	/*
		case SDLK_LEFT:
			e = board->checkUnitsInAOE(unit->getX()-1,unit->getY(),activeSpell->getRange(),BOARD_AXIS_X_MINUS,activeSpell->getAreaOfEffect(),&targets);
			break;
		case SDLK_DOWN:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()+1,activeSpell->getRange(),BOARD_AXIS_Y,activeSpell->getAreaOfEffect(),&targets);
			break;
		case SDLK_RIGHT:
			e = board->checkUnitsInAOE(unit->getX()+1,unit->getY(),activeSpell->getRange(),BOARD_AXIS_X,activeSpell->getAreaOfEffect(),&targets);
			break;
		case SDLK_UP:
			e = board->checkUnitsInAOE(unit->getX(),unit->getY()-1,activeSpell->getRange(),BOARD_AXIS_Y_MINUS,activeSpell->getAreaOfEffect(),&targets);
			break;
		*/
	}

	if (e == T_SUCCESS) {
		context = CONTEXT_SPELL_EFFECT;
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

	showUnitMenu();
	return T_SUCCESS;
}

T_ERROR GameManager::useSpell(vector<Unit*> *targets){
	Unit* unit = *activeUnit;

	T_ERROR e = T_SUCCESS;
			//activeSpell->perform(this, targets);
	if (e == T_SUCCESS){
		actionsPerTurn--;
		if (getOtherTeamBodyCount(unit->getTeam()) == 0){
			endGame();
			return T_SUCCESS;
		}
	} else {
//		std::cerr << "Erro ao usar a spell " << activeSpell << " e=" << e << std::endl;
	}

	context = CONTEXT_UNIT_MENU;
	showUnitMenu();

	return T_SUCCESS;
}

void GameManager::showEndScreen(){
	menu.show();
}

void GameManager::update(SDL_Renderer* r,TTF_Font *font,SDL_Rect*drawArea){

	if (context == CONTEXT_IDLE)
		return;

	showMap(r);
	showHighlightedMouse(r);
	
	Unit* unit = *activeUnit;
	BOARD_AOE area;

	if (context == CONTEXT_UNIT_MENU) {
		showUnitMenu();

		area.x = (*activeUnit)->getX();
		area.y = (*activeUnit)->getY();
		area.range = 0;
		area.shape = AOE_SHAPE_POINT;

		showHighlightedArea(r,&area);
	} else if (context == CONTEXT_UNIT_SELECT_MOVE) {

		area.x = (*activeUnit)->getX();
		area.y = (*activeUnit)->getY();
		area.range = movesPerTurn;
		area.shape = AOE_SHAPE_CIRCLE;

		showUnitMenu();
		showHighlightedArea(r,&area);
	} else if (context == CONTEXT_UNIT_SELECT_TARGET) {

		area.x = (*activeUnit)->getX();
		area.y = (*activeUnit)->getY();
		area.range = (*activeUnit)->getRange();
		area.shape = AOE_SHAPE_CROSS;

		showUnitMenu();
		showHighlightedArea(r,&area);
	} else if (context == CONTEXT_UNIT_MOVE) {
		if (! unit->isAnimating()) {
			//Fim da animacao de movimento
			//Trocando de contexto
			context = CONTEXT_UNIT_MENU;
			showUnitMenu();
			unit->setAnimation(Animation());
		}
	} else if (context == CONTEXT_UNIT_COMBAT){
		if (! unit->isAnimating()){
			context = CONTEXT_UNIT_MENU;
			showUnitMenu();
			unit->setAnimation(Animation());
		}
	}
	
	for (std::vector<Unit*>::iterator it=unitList.begin(); it != unitList.end(); it++)
		showUnit(*it,r,font);

	if (context == CONTEXT_END_GAME){
		showEndScreen();
	}

}

void GameManager::showUnit(Unit* unit,SDL_Renderer *r, TTF_Font* font){
	Screen::drawUnit(unit,r,font);
}

void GameManager::showHighlightedArea(SDL_Renderer*r,BOARD_AOE* area){
	Screen::drawHighlightedArea(r,board,area,context);
}

void GameManager::showHighlightedMouse(SDL_Renderer*r){
	BOARD_AOE area;
	if (Screen::mouseBoardPosition(board,&area) == T_SUCCESS){
		Screen::drawHighlightedArea(r,board,&area,CONTEXT_IDLE);
	}
}
