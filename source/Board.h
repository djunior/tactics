#ifndef __BOARD_H__
#define __BOARD_H__

#include "Unit.h"
#include "utils/t_error.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

enum AOE_SHAPE {
	AOE_SHAPE_LINE,
	AOE_SHAPE_CONE,
	AOE_SHAPE_SQUARE,
	AOE_SHAPE_CROSS,
};

enum BOARD_AXIS {
	BOARD_AXIS_X,
	BOARD_AXIS_Y,
	BOARD_AXIS_X_MINUS,
	BOARD_AXIS_Y_MINUS,
};

typedef enum BOARD_AXIS BOARD_AXIS;
typedef enum AOE_SHAPE AOE_SHAPE;

class Board {
private:
	 Unit* boardMap[8][8];
	 unsigned int maxBoardWidth,maxBoardLength;

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
