/*
 * Fireball.cpp
 *
 *  Created on: Feb 22, 2014
 *      Author: djunior
 */

#include "fireball.h"

Fireball::Fireball(Unit* u) : Spell(u) {
	// TODO Auto-generated constructor stub
	damage = 30;
	manaCost = 5;
	cooldown = 2;
	aoe = AOE_SHAPE_LINE;
	range = 5;
	radius = 1;
	delay = 0;
	spellName = "Fireball";
}

Fireball::~Fireball() {
	// TODO Auto-generated destructor stub
}

T_ERROR Fireball::perform(GameManager *gm){
	return T_SUCCESS;
}

T_ERROR Fireball::perform(GameManager *gm, Unit * target){
	if (target->getTeam() == owner->getTeam())
		return T_ERROR_INVALID_TARGET;

	std::cout << "Fireball(" << this << ") partindo da unidade: " << owner << " para a unidade: " << target << " causando " << damage << " de dano" << std::endl;

	target->takeDamage(damage);

	if (target->isDead())
		gm->notifyDeath(target->getTeam(),1);

	return T_SUCCESS;
}

T_ERROR Fireball::perform(GameManager *gm, std::vector<Unit *> *targetList){

	if (targetList->empty())
		return T_ERROR_INVALID_TARGET;

	Unit * target = targetList->front();

	return perform(gm,target);

}
