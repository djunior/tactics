#ifndef __BOARD_H__
#define __BOARD_H__

#include "Unit.h"
#include "utils/t_error.h"
#include <vector>

using namespace std;

class Board {
private:
	 Unit* boardMap[8][8];
	 unsigned int maxBoardWidth,maxBoardLength;

public:
	Board(int width, int length);
	T_ERROR moveUnit(Unit* u, unsigned int x, unsigned int y);
	T_ERROR addUnit(Unit* u, unsigned int x, unsigned int y);
	vector<Unit*> checkUnitsInVicinity(Unit* u, unsigned int range);
};



#endif
