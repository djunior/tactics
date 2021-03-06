/*
 * Wizard.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef WIZARD_H_
#define WIZARD_H_

#include "../unit.h"
#include "../utils/t_team.h"
//#include "../spells/fireball.h"
#include "../utils/sprite.h"

#define WIZARD_HP 40
#define WIZARD_DAMAGE 10
#define WIZARD_RANGE 3
#define WIZARD_MOVE 1
#define WIZARD_ARMOR 1
#define WIZARD_MANA_POOL 20

#define WIZARD_SPRITE "images\\RBA_Wizard.png"
#define WIZARD_PROJECTILE_SPRITE "images\\missile.png"

class Wizard : public Unit{
private:
	void selectFrameIdle(SDL_Rect*);
	void selectFrameMove(int, SDL_Rect *);
	void selectFrameAttack(int,SDL_Rect*);
	void selectFrameTakeDamage(int,SDL_Rect*);

public:
	Wizard(T_TEAM t,SDL_Renderer *r, SDL_Window *w);

	void selectFrame(int frameIndex, ANIMATION_TYPE type, SDL_Rect* rect);
	int getFramesAnimation(ANIMATION_TYPE type);
	virtual ~Wizard();

	void initUnitStats();
};

#endif /* WIZARD_H_ */
