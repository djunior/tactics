/*
 * Spell.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef SPELL_H_
#define SPELL_H_

#include <vector>
#include "utils/t_error.h"
#include "utils/board_utils.h"
#include "unit.h"
#include "gameManager.h"
#include <string>

//Forward declaration

class Spell {
protected:
	unsigned int manaCost, cooldown, range, radius, delay;
	int damage;
	Unit * owner;
	AOE_SHAPE aoe;
	std::string spellName;

public:
	Spell(Unit * u);
	virtual ~Spell();

	unsigned int getManaCost();
	unsigned int getCooldown();
	unsigned int getRange();
	unsigned int getRadius();
	unsigned int getDelay();
	int getDamage();
	AOE_SHAPE getAreaOfEffect();
	std::string getName();

	virtual T_ERROR perform(GameManager *gm) = 0;
	virtual T_ERROR perform(GameManager *gm, Unit * target) = 0;
	virtual T_ERROR perform(GameManager *gm, std::vector<Unit *> *targetList) = 0;

	void debug_showStats(bool verbose);
};

#endif /* SPELL_H_ */
