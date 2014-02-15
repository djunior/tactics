#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "Board.h"
#include "Unit.h"
#include <vector>

class GameManager{
private:
	vector<Unit> unitList;
	Board* b;
	unsigned int turn;

public:
	GameManager(Board* newBoard);

	void addUnit();
	void startTurn();
	void startGame();
	unsigned int getTurn();
};

#endif
