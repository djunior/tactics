#ifndef __BOARD_H__
#define __BOARD_H__

#include "unit.h"
#include "utils/t_error.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "utils/board_utils.h"
using namespace std;

class Board {
private:
	 Unit* boardMap[8][8];
	 unsigned int maxBoardX,maxBoardY;

public:
	Board(int width, int length);
	Unit* getUnitAt(unsigned int x, unsigned int y);
	T_ERROR moveUnit(Unit* u, unsigned int x, unsigned int y);
	T_ERROR addUnit(Unit* u, unsigned int x, unsigned int y);
	T_ERROR addUnit(Unit* u);
	T_ERROR removeUnit(Unit* unit);
	T_ERROR checkUnitsInVicinity(Unit* u, unsigned int range, vector<Unit*> *targetList);
	T_ERROR checkUnitsInAOE(int x, int y, int range,BOARD_AXIS axis, AOE_SHAPE shape, vector<Unit *> *targetList);
	void debug_showMap();
};



#endif
