#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "Board.h"
#include "Knight.h"
#include "Wizard.h"
#include <vector>
#include "utils/t_team.h"

#define GAMEMANAGER_INITIAL_TURN 0;

class GameManager{
private:
	vector<Unit *> unitList;
	Board* board;
	unsigned int turn;

public:
	GameManager(Board* newBoard);
	~GameManager();
	void createUnit(string unitClass,T_TEAM team);
	void startTurn();
	void startGame();
	unsigned int getTurn();
};

#endif
