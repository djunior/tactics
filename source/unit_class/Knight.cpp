/*
 * Knight.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "Knight.h"

Knight::Knight(T_TEAM t)  : Unit (t) {
	hp = KNIGHT_HP;
	attackDamage = KNIGHT_DAMAGE;
	armor = KNIGHT_ARMOR;
	move = KNIGHT_MOVE;
	range = KNIGHT_RANGE;
	unitClassName = "Knight";
	mana = KNIGHT_MANA_POOL;
	manaPool = KNIGHT_MANA_POOL;
}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

