/*
 * FpsControl.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: djunior
 */

#include "fpsControl.h"

FpsControl::FpsControl(int limit_fps) {
	// TODO Auto-generated constructor stub
	frameDuration = (float) 1000/limit_fps;
	lastTick = SDL_GetTicks();
}

FpsControl::~FpsControl() {
	// TODO Auto-generated destructor stub
}

bool FpsControl::isFrameDone(){
	float currentTick = SDL_GetTicks();
	float duration = currentTick - lastTick;
	if (duration >= frameDuration){
		lastTick = currentTick;
		return true;
	}
	return false;
}
