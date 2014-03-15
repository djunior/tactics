/*
 * board_utils.h
 *
 *  Created on: Feb 22, 2014
 *      Author: djunior
 */

#ifndef BOARD_UTILS_H_
#define BOARD_UTILS_H_

enum AOE_SHAPE {
	AOE_SHAPE_POINT,
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

struct BOARD_AOE{
	int x;
	int y;
	int range;
	AOE_SHAPE shape;
	BOARD_AXIS axis;
};

typedef enum BOARD_AXIS BOARD_AXIS;
typedef enum AOE_SHAPE AOE_SHAPE;
typedef struct BOARD_AOE BOARD_AOE;

class Board;

#endif /* BOARD_UTILS_H_ */
