/*
 * Wizard.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef WIZARD_H_
#define WIZARD_H_

#include "../Unit.h"
#include "../utils/t_team.h"
#include "../spells/Fireball.h"

#define WIZARD_HP 40
#define WIZARD_DAMAGE 10
#define WIZARD_RANGE 2
#define WIZARD_MOVE 1
#define WIZARD_ARMOR 1
#define WIZARD_MANA_POOL 20

class Wizard : public Unit{
public:
	Wizard(T_TEAM t);
	virtual ~Wizard();
};

#endif /* WIZARD_H_ */