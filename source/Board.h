#ifndef __BOARD_H__
#define __BOARD_H__

#include "Unit.h"
#include "utils/t_error.h"
#include <vector>
#include <iostream>

using namespace std;

class Board {
private:
	 Unit* boardMap[8][8];
	 unsigned int maxBoardWidth,maxBoardLength;

public:
	Board(int width, int length);
	T_ERROR moveUnit(Unit* u, unsigned int x, unsigned int y);
	T_ERROR addUnit(Unit* u, unsigned int x, unsigned int y);
	T_ERROR addUnit(Unit* u);
	void debug_showMap();
	vector<Unit*> checkUnitsInVicinity(Unit* u, unsigned int range);
	Unit* getUnitAt(unsigned int x, unsigned int y);
	T_ERROR removeUnit(Unit* unit);
};



#endif
