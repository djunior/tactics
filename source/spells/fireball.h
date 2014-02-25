/*
 * Fireball.h
 *
 *  Created on: Feb 22, 2014
 *      Author: djunior
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "../spell.h"

class Fireball : public Spell {
public:
	Fireball(Unit* owner);
	virtual ~Fireball();

	T_ERROR perform(GameManager *gm);
	T_ERROR perform(GameManager *gm, Unit *target);
	T_ERROR perform(GameManager *gm, std::vector<Unit *> *targetList);
};

#endif /* FIREBALL_H_ */
