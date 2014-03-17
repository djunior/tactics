/*
 * Wizard.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "wizard.h"

Wizard::Wizard(T_TEAM t,SDL_Renderer *r) : Unit(t,r) {

	hp = WIZARD_HP;
	maxHp = WIZARD_HP;
	attackDamage = WIZARD_DAMAGE;
	armor = WIZARD_ARMOR;
	move = WIZARD_MOVE;
	range = WIZARD_RANGE;
	attackArea = AOE_SHAPE_LINE;
	unitClassName = "Wizard";
	Fireball *fireball = new Fireball(this);
	spellList.push_back(fireball);
	mana = WIZARD_MANA_POOL;
	manaPool = WIZARD_MANA_POOL;
}

Wizard::~Wizard() {
	// TODO Auto-generated destructor stub
}

