/*
 * Wizard.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "Wizard.h"

Wizard::Wizard(T_TEAM t) : Unit(t) {

	hp = WIZARD_HP;
	attackDamage = WIZARD_DAMAGE;
	armor = WIZARD_ARMOR;
	move = WIZARD_MOVE;
	range = WIZARD_RANGE;
	attackArea = AOE_SHAPE_LINE;
	unitClassName = "Wizard";
	Fireball *fireball = new Fireball(this);
	spellList.push_back(fireball);
}

Wizard::~Wizard() {
	// TODO Auto-generated destructor stub
}

