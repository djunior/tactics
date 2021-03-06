/*
 * Knight.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "../unit.h"
#include "../utils/t_team.h"
#include "../utils/sprite.h"

#define KNIGHT_HP 80
#define KNIGHT_DAMAGE 20
#define KNIGHT_RANGE 1
#define KNIGHT_MOVE 2
#define KNIGHT_ARMOR 5
#define KNIGHT_MANA_POOL 10

#define KNIGHT_SPRITE "images\\RBA_Swordsman.png"

class Knight : public Unit {
private:
	void selectFrameIdle(SDL_Rect*);
	void selectFrameMove(int, SDL_Rect *);
	void selectFrameAttack(int,SDL_Rect*);
	void selectFrameTakeDamage(int,SDL_Rect*);

public:
	Knight(T_TEAM t,SDL_Renderer *r, SDL_Window *w);

	void selectFrame(int frameIndex, ANIMATION_TYPE type, SDL_Rect *rect);
	int getFramesAnimation(ANIMATION_TYPE type);
	virtual ~Knight();

	void initUnitStats();
};

#endif /* KNIGHT_H_ */
