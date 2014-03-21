/*
 * animation.h
 *
 *  Created on: Mar 17, 2014
 *      Author: djunior
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "utils/board_utils.h"
#include <iostream>

enum ANIMATION_TYPE{
	ANIMATION_IDLE,
	ANIMATION_UNIT_MOVE,
	ANIMATION_UNIT_ATTACK
};

typedef enum ANIMATION_TYPE ANIMATION_TYPE;

class Animation {
public:
	BOARD_POINT startPoint, endPoint;
	ANIMATION_TYPE type;
	double currentFrame,duration;
	int repeatFrame;

	Animation(ANIMATION_TYPE,BOARD_POINT, BOARD_POINT,double,int);
	Animation();

	bool hasStarted();
	bool hasEnded();

	virtual ~Animation();

	void debug_showStats();
};

#endif /* ANIMATION_H_ */
