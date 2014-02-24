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
	damage = 0;
	owner = u;
	aoe = AOE_SHAPE_POINT;
	spellName = "BaseSpell";
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

AOE_SHAPE Spell::getAreaOfEffect(){
	return aoe;
}

std::string Spell::getName(){
	return spellName;
}

int Spell::getDamage(){
	return damage;
}

void Spell::debug_showStats(bool verbose){

	std::cout << "Spell: ( " << spellName << "," << this << ") stats:"<< std::endl;
	std::cout << "Spell: ( " << spellName << "," << this << ") Owner: class=" << owner->getClassName() << " ptr=" << owner << std::endl;
	std::cout << "Spell: ( " << spellName << "," << this << ") Mana cost: " << manaCost << std::endl;
	std::cout << "Spell: ( " << spellName << "," << this << ") Damage: " << damage << std::endl;

	if (verbose) {
		std::cout << "Spell: ( " << spellName << "," << this << ") Cooldown: " << cooldown << std::endl;
		std::cout << "Spell: ( " << spellName << "," << this << ") Range: " << range << std::endl;
		std::cout << "Spell: ( " << spellName << "," << this << ") Radius: " << radius << std::endl;
		std::cout << "Spell: ( " << spellName << "," << this << ") Delay: " << delay << std::endl;
		std::cout << "Spell: ( " << spellName << "," << this << ") AOE: " << aoe << std::endl;
	}

}
