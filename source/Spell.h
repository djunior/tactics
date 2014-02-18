/*
 * Spell.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef SPELL_H_
#define SPELL_H_

#include <vector>

//Forward declaration
class Unit;

class Spell {
protected:
	Unit* owner;
	unsigned int manaCost, cooldown, range, radius, delay;

public:
	Spell(Unit * u);
	virtual ~Spell();

	unsigned int getManaCost();
	unsigned int getCooldown();
	unsigned int getRange();
	unsigned int getRadius();
	unsigned int getDelay();

	virtual void perform() = 0;
	virtual void perform(Unit * target) = 0;
	virtual void perform(std::vector<Unit *> *targetList) = 0;
};

#endif /* SPELL_H_ */
