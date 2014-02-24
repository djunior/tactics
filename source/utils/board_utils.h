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

typedef enum BOARD_AXIS BOARD_AXIS;
typedef enum AOE_SHAPE AOE_SHAPE;

class Board;

#endif /* BOARD_UTILS_H_ */
