/*
 * Unit.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */


#include "Unit.h"

Unit::Unit (T_TEAM t){
	x = 0;
	y = 0;
	hp = UNIT_DEFAULT_HP;
	attackDamage = UNIT_DEFAULT_DAMAGE;
	armor = UNIT_DEFAULT_ARMOR;
	level = UNIT_DEFAULT_LEVEL;
	move = UNIT_DEFAULT_MOVE;
	speed = UNIT_DEFAULT_SPEED;
	range = UNIT_DEFAULT_RANGE;
	dead = false;
	team = t;
}

unsigned int Unit::getX(){
	return x;
}

unsigned int Unit::getY(){
	return y;
}

void Unit::setX(unsigned int _x){
	x = _x;
}

void Unit::setY(unsigned int _y){
	y = _y;
}

void Unit::setOrigin(unsigned int x, unsigned int y){
	setX(x);
	setY(y);
}

void Unit::kill(){
	dead = true;
}

bool Unit::isDead(){
	return dead;
}

T_TEAM Unit::getTeam(){
	return team;
}

int Unit::getSpeed(){
	return speed;
}

unsigned int Unit::getHp(){
	return hp;
}

unsigned int Unit::getMove(){
	return move;
}

unsigned int Unit::getRange(){
	return range;
}

bool Unit::takeDamage(unsigned int rawDamage){
	// Essa formula de dano pode ser alterada caso seja implementado
	// stats defensivos, como armor, armor class, etc
	hp -= rawDamage;

	if (hp < 0)
		kill();

	return isDead();
}



