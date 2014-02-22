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
	actionPerTurn = UNIT_DEFAULT_ACTION_PER_TURN;
	attackArea = AOE_SHAPE_POINT;
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
	std::cout << "Unit(" << this << ") x= " << _x << std::endl;
	x = _x;
}

void Unit::setY(unsigned int _y){
	y = _y;
}

void Unit::setOrigin(unsigned int x, unsigned int y){
	setX(x);
	setY(y);
}

AOE_SHAPE Unit::getAttackArea(){
	return attackArea;
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
	std::cout << "Unidade: " << this << " com " << hp << " de hp recebendo " << rawDamage << " de dano" << std::endl;
	// Essa formula de dano pode ser alterada caso seja implementado
	// stats defensivos, como armor, armor class, etc
	hp -= rawDamage;
	std::cout << "Unidade " << this << " com " << hp << " de hp apos o combate" << std::endl;
	if (hp <= 0)
		kill();

	return isDead();
}

unsigned int Unit::getAttackDamage(){
	// Essa função deve calcular o dano que essa unidade causa ao atacar, eventualmente, podemos implementar
	// criticos ou outros modificadores de dano que seriam calculados aqui
	return attackDamage;
}

T_ERROR Unit::combat(std::vector<Unit *> *targetList,int *bodyCount){

	Unit *target = targetList->front();

	std::cout << "Unidade: " << this << " atacando unidade: " << target << " com " << getAttackDamage() << " de dano" << std::endl;

	if (target->getTeam() == getTeam())
		return T_ERROR_INVALID_UNIT;

	if (target->takeDamage(getAttackDamage()))
		(*bodyCount)--;

	return T_SUCCESS;
}

unsigned int Unit::getActionsPerTurn(){
	return actionPerTurn;
}

void Unit::debug_showStats(){
	std::cout << "Unit (" << this << ") stats:" << std::endl;
	std::cout << "Unit (" << this << ") x: " << x << std::endl;
	std::cout << "Unit (" << this << ") y: " << y << std::endl;
	std::cout << "Unit (" << this << ") hp: " << hp << std::endl;
	std::cout << "Unit (" << this << ") attackDamage: " << attackDamage << std::endl;
	std::cout << "Unit (" << this << ") armor: " << armor << std::endl;
	std::cout << "Unit (" << this << ") level: " << level << std::endl;
	std::cout << "Unit (" << this << ") move: " << move << std::endl;
	std::cout << "Unit (" << this << ") range: " << range << std::endl;
	std::cout << "Unit (" << this << ") speed: " << speed << std::endl;
	std::cout << "Unit (" << this << ") dead: " << dead << std::endl;
	std::cout << "Unit (" << this << ") team: " << team << std::endl;
}


