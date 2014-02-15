#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "Board.h"
#include "Unit.h"
#include <vector>

#define GAMEMANAGER_INITIAL_TURN 0;

class GameManager{
private:
	vector<Unit> unitList;
	Board* board;
	unsigned int turn;

public:
	GameManager(Board* newBoard);

	void addUnit();
	void startTurn();
	void startGame();
	unsigned int getTurn();
};

#endif
