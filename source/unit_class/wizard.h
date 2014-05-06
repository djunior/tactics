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
#define WIZARD_RANGE 2
#define WIZARD_MOVE 1
#define WIZARD_ARMOR 1
#define WIZARD_MANA_POOL 20

#define WIZARD_SPRITE "images\\M_Wizard.png"

class Wizard : public Unit{
public:
	Wizard(T_TEAM t,SDL_Renderer *r, SDL_Window *w);
	virtual ~Wizard();
};

#endif /* WIZARD_H_ */
