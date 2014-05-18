/*
 * animation.cpp
 *
 *  Created on: Mar 17, 2014
 *      Author: djunior
 */

#include "animation.h"

Animation::Animation(ANIMATION_TYPE t, BOARD_POINT start, BOARD_POINT end, double dur, int rep, int frames) {
	type = t;

	currentFrame = 0;
	duration = dur;

	startPoint = start;
	endPoint = end;

	repeatFrame = rep;

	numberFrames = frames;
}

// Default initiation;
Animation::Animation() {
	type = ANIMATION_IDLE;

	currentFrame = 1;
	duration = 1;

	startPoint.x = 0;
	startPoint.y = 0;

	endPoint.x = 0;
	endPoint.y = 0;

	repeatFrame = 1;

	numberFrames = 1;
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

bool Animation::hasStarted() {
	return currentFrame > 0;
}

bool Animation::hasEnded() {
	return currentFrame >= duration;
}

void Animation::debug_showStats() {
	std::cout << "Animation(" << this << ") stats:" << std::endl;
	std::cout << "Type: " << type << std::endl;
	std::cout << "Number of frames: " << numberFrames << std::endl;
	std::cout << "Duration: " << duration << std::endl;
	std::cout << "Current Frame: " << currentFrame << std::endl;
	std::cout << "Start Point(" << &startPoint << "): (" << startPoint.x << ","
			<< startPoint.y << ")" << std::endl;
	std::cout << "End Point(" << &endPoint << "): (" << endPoint.x << ","
			<< endPoint.y << ")" << std::endl;
}
