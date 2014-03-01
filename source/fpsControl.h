/*
 * FpsControl.h
 *
 *  Created on: Mar 1, 2014
 *      Author: djunior
 */

#ifndef FPSCONTROL_H_
#define FPSCONTROL_H_

#include "stdint.h"
#include "SDL2/SDL.h"

class FpsControl {
private:
	float lastTick;
	float frameDuration;

public:
	FpsControl(int limit_fps);
	bool isFrameDone();
	virtual ~FpsControl();
};

#endif /* FPSCONTROL_H_ */
