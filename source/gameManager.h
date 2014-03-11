#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "board.h"
#include <vector>
#include <map>
#include "utils/t_team.h"
#include "SDL2/SDL.h"

#include "drawFunctions.h"

#define GAMEMANAGER_INITIAL_TURN 0;

enum GAME_MANAGER_CONTEXT {
	IDLE,
	UNIT_MENU,
	SPELL_MENU,
	SPELL_EFFECT,
	UNIT_COMBAT,
	UNIT_MOVE,
	UNIT_SELECT_TARGET,
	SPELL_SELECT_TARGET,
	BEGINNING_TURN,
	ENDING_TURN,
	BEGINNING_UNIT_TURN,
	ENDING_UNIT_TURN,
};

typedef enum GAME_MANAGER_CONTEXT GAMEMANAGER_CONTEXT;

class GameManager{
private:
	vector<Unit *> unitList;
	//std::map<std::string,Spell *> spellMap;
	Board* board;
	std::vector<Unit*>::iterator activeUnit;
	int actionsPerTurn;
	int movesPerTurn;
	Spell* activeSpell;
	unsigned int turn;
	int teamABodyCount, teamBBodyCount;
	GAMEMANAGER_CONTEXT context;
	SDL_Renderer* renderer;

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
	void showMap(TTF_Font *);
	void showUnit(Unit*);
	void showUnit(Unit*,SDL_Renderer*,TTF_Font *);
	void showUnitMenu();
	void showSpellMenu();
	void showMoveOptions();
	void showAttackOptions();
	void showTargetOptions();

public:
	GameManager(Board* newBoard,SDL_Renderer* r);
	~GameManager();
	void createUnit(string unitClass,T_TEAM team);
	void startGame();
	void startTurn();
	void endGame();
	void notifyDeath(T_TEAM team, int casualties);
	void processEvent(SDL_Event* event);
	void update(SDL_Renderer*,TTF_Font*,SDL_Rect*);
	unsigned int getTurn();
};

#endif
