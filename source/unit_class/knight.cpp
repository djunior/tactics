/*
 * Knight.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "knight.h"

Knight::Knight(T_TEAM t,SDL_Renderer *r, SDL_Window *w)  : Unit (t,r,w) {
	hp = KNIGHT_HP;
	attackDamage = KNIGHT_DAMAGE;
	armor = KNIGHT_ARMOR;
	move = KNIGHT_MOVE;
	range = KNIGHT_RANGE;
	unitClassName = "Knight";
	mana = KNIGHT_MANA_POOL;
	manaPool = KNIGHT_MANA_POOL;

	menu.setImage(KNIGHT_SPRITE);
	menu.statsMenu();
}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

