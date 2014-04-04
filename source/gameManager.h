#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "menu.h"
#include "board.h"
#include <vector>
#include <map>
#include "utils/t_team.h"
#include "SDL2/SDL.h"

#include "drawFunctions.h"

#define GAMEMANAGER_INITIAL_TURN 0;

enum GAME_MANAGER_CONTEXT {
	CONTEXT_IDLE,
	CONTEXT_UNIT_MENU,
	CONTEXT_SPELL_MENU,
	CONTEXT_SPELL_EFFECT,
	CONTEXT_UNIT_COMBAT,
	CONTEXT_UNIT_MOVE,
	CONTEXT_UNIT_SELECT_MOVE,
	CONTEXT_UNIT_SELECT_TARGET,
	CONTEXT_SPELL_SELECT_TARGET,
	CONTEXT_BEGINNING_TURN,
	CONTEXT_ENDING_TURN,
	CONTEXT_BEGINNING_UNIT_TURN,
	CONTEXT_ENDING_UNIT_TURN,
	CONTEXT_END_GAME,
};

typedef enum GAME_MANAGER_CONTEXT GAMEMANAGER_CONTEXT;

enum UNIT_CLASS {
	UNIT_CLASS_WIZARD,
	UNIT_CLASS_KNIGHT,
	UNIT_CLASS_UNIT,
};

typedef enum UNIT_CLASS UNIT_CLASS;

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

	void cleanup();
	int getOtherTeamBodyCount(T_TEAM team);
	T_ERROR startUnitTurn(Unit* u);
	T_ERROR startNextUnitTurn();
	T_ERROR endUnitTurn();
	T_ERROR startNextTurn();
	T_ERROR endTurn();
	T_ERROR moveUnit(SDL_Keycode);
	T_ERROR selectCombatTarget(SDL_Keycode key);
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
	void showEndScreen();

public:
	GameManager(Board* newBoard,SDL_Renderer* r, SDL_Window *w);
	~GameManager();
	void createUnit(UNIT_CLASS unitClass,T_TEAM team);
	void startGame();
	void startTurn();
	void endGame();
	void notifyDeath(T_TEAM team, int casualties);
	void processEvent(SDL_Event* event);
	void update(SDL_Renderer*,TTF_Font*,SDL_Rect*);
	unsigned int getTurn();
};

#endif
