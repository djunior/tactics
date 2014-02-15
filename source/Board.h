#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "Unit.h"
#include "t_error.h"

class Board {
private:
	 vector < vector <Unit*> > boardMap;

public:
	Board(int width, int length);
	T_ERROR moveUnit(Unit* u, unsigned int x, unsigned int y);
	vector<Unit*> checkUnitsInVicinity(Unit* u, unsigned int range);
};



#endif
