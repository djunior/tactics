/*
 * Spell.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "Spell.h"

Spell::Spell(Unit* u) {
	cooldown = 0;
	manaCost = 0;
	delay = 0;
	radius = 0;
	range = 0;
	owner = u;
}

Spell::~Spell() {
	// TODO Auto-generated destructor stub
}

unsigned int Spell::getCooldown(){
	return cooldown;
}

unsigned int Spell::getDelay(){
	return delay;
}

unsigned int Spell::getRadius(){
	return radius;
}

unsigned int Spell::getManaCost(){
	return manaCost;
}

unsigned int Spell::getRange(){
	return range;
}

