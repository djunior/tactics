/*
 * Unit.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */


#include "unit.h"
#include "spell.h"

Unit::Unit (T_TEAM t){
	x = 0;
	y = 0;
	hp = UNIT_DEFAULT_HP;
	maxHp = UNIT_DEFAULT_HP;
	attackDamage = UNIT_DEFAULT_DAMAGE;
	armor = UNIT_DEFAULT_ARMOR;
	level = UNIT_DEFAULT_LEVEL;
	move = UNIT_DEFAULT_MOVE;
	speed = UNIT_DEFAULT_SPEED;
	range = UNIT_DEFAULT_RANGE;
	actionPerTurn = UNIT_DEFAULT_ACTION_PER_TURN;
	unitClassName = "UnitBase";
	attackArea = AOE_SHAPE_POINT;
	mana = UNIT_DEFAULT_MANA_POOL;
	manaPool = UNIT_DEFAULT_MANA_POOL;
	dead = false;
	team = t;
}

Unit::~Unit(){
	for (std::vector<Spell*>::iterator it=spellList.begin(); it != spellList.end(); it++){
		delete (*it);
	}
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

unsigned Unit::getMaxHp(){
	return maxHp;
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

	if (targetList->empty())
		return T_ERROR_INVALID_TARGET;

	Unit *target = targetList->front();

	std::cout << "Unidade: " << this << " atacando unidade: " << target << " com " << getAttackDamage() << " de dano" << std::endl;

	if (target->getTeam() == getTeam())
		return T_ERROR_INVALID_TARGET;

	if (target->takeDamage(getAttackDamage()))
		(*bodyCount)--;

	return T_SUCCESS;
}

unsigned int Unit::getActionsPerTurn(){
	return actionPerTurn;
}

void Unit::debug_showStats(bool verbose){
	std::cout << "Unit (" << unitClassName << "," << this << ") stats:" << std::endl;
	std::cout << "Unit (" << unitClassName << "," << this << ") x: " << x << " y: " << y << std::endl;
	std::cout << "Unit (" << unitClassName << "," << this << ") hp: " << hp << std::endl;
	std::cout << "Unit (" << unitClassName << "," << this << ") team: " << team << std::endl;
	if (verbose) {
		std::cout << "Unit (" << unitClassName << "," << this << ") attackDamage: " << attackDamage << std::endl;
		std::cout << "Unit (" << unitClassName << "," << this << ") armor: " << armor << std::endl;
		std::cout << "Unit (" << unitClassName << "," << this << ") level: " << level << std::endl;
		std::cout << "Unit (" << unitClassName << "," << this << ") move: " << move << std::endl;
		std::cout << "Unit (" << unitClassName << "," << this << ") range: " << range << std::endl;
		std::cout << "Unit (" << unitClassName << "," << this << ") speed: " << speed << std::endl;
		std::cout << "Unit (" << unitClassName << "," << this << ") dead: " << dead << std::endl;
	}
}

std::string Unit::getClassName(){
	return unitClassName;
}

void Unit::debug_showStats(){
	debug_showStats(false);
}

std::vector<Spell *> *Unit::getSpellList(){
	return &spellList;
}

unsigned int Unit::getMana(){
	return mana;
}

void Unit::setMana(int amount){
	mana = amount;
	if (mana > manaPool)
		mana = manaPool;
}
