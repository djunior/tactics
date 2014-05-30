#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "menu.h"
#include "board.h"
#include <vector>
#include <map>
#include "utils/t_team.h"
#include "SDL2/SDL.h"

#include "drawFunctions.h"
#include "basic_includes.h"

#define GAMEMANAGER_INITIAL_TURN 0;

/*
 * Classe GameManager
 *
 * Essa classe é a principal do jogo. Ela é responsável por receber as entradas do usuário, controlar o fluxo do jogo, e decidir o que aparece na tela.
 *
 * O fluxo dos turnos é controlado pelas entradas do usuario e o contexto atual ( os contextos estao definidos no arquivo basic_includes.h)
 *
 * Dependendo da combinação entrada/contexto, as funções de troca de turno/troca de unidade são chamados. Um turno normalmente ocorre da seguinte forma:
 *
 * startNextTurn() - troca o contexto para CONTEXT_BEGINNING_TURN e altera o iterador activeUnit para a primeira unidade do vector unitList
 * startNextUnitTurn() - troca o contexto para CONTEXT_UNIT_MENU, e aguarda uma entrada do usuario. A entrada pode ser para mover a unidade, atacar, ou pular turno.
 * endUnitTurn() - troca o contexto para CONTEXT_ENDING_UNIT_TURN e incrementa o iterador activeUnit.
 *
 * Se o activeUnit estiver apontando para a ultima unidade da lista, a proxima função chamada é endTurn(). Senao, é chamado startNextUnitTurn().
 *
 * endTurn() - troca o contexto para CONTEXT_ENDING_TURN e chama a função startNextTurn(), voltando para o começo
 *
 */
class GameManager{
private:
	vector<Unit *> unitList;
	//std::map<std::string,Spell *> spellMap;
	Board* board;
	std::vector<Unit*>::iterator activeUnit;
	int actionsPerTurn;
	int movesPerTurn;
//	Spell* activeSpell;
	unsigned int turn;
	int teamABodyCount, teamBBodyCount;
	GAMEMANAGER_CONTEXT context;
	SDL_Renderer* renderer;
	SDL_Window* window;
	T_TEAM winningTeam;
	mWindow menu;
	mWindow menuUnitAction;

	void cleanup();
	int getOtherTeamBodyCount(T_TEAM team);
	T_ERROR startUnitTurn(Unit* u);
	T_ERROR startNextUnitTurn();
	T_ERROR endUnitTurn();
	T_ERROR startNextTurn();
	T_ERROR endTurn();
	T_ERROR moveUnit(SDL_Keycode);
	T_ERROR moveUnit();
	T_ERROR selectCombatTarget(SDL_Keycode key);
	T_ERROR selectCombatTarget();
	T_ERROR combat(vector<Unit*> *targets);
	T_ERROR useSpell(vector<Unit*> *targets);
	T_ERROR selectSpellTargets(SDL_Keycode key);

	void showMap();
	void showMap(SDL_Renderer *);
	void showUnit(Unit*);
	void showUnit(Unit*,SDL_Renderer*,TTF_Font *);
	void showUnitMenu();
	void showSpellMenu();
	void showMoveOptions();
	void showAttackOptions();
	void showTargetOptions();
	void showHighlightedArea(SDL_Renderer*,BOARD_AOE*);
	void showHighlightedMouse(SDL_Renderer*);
	void showEndScreen();

public:
	GameManager(Board* newBoard,SDL_Renderer* r, SDL_Window *w);
	~GameManager();
	void createUnit(UNIT_CLASS unitClass,T_TEAM team);
	void startGame();
	void startTurn();
	void endGame();
	void notifyDeath(T_TEAM team, int casualties);
	void update(SDL_Renderer*,TTF_Font*,SDL_Rect*);
	unsigned int getTurn();

	// O valor de retorno indica se o programa desse ser encerrado (true) ou não (false)
	bool processEvent(SDL_Event* event);
	bool processMouseEvent(SDL_Event* event);
};

#endif
