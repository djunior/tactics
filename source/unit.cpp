/*
 * Unit.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */


#include "unit.h"
//#include "spell.h"

Unit::Unit (T_TEAM t,SDL_Renderer *renderer, SDL_Window *window){
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
	image = UNIT_DEFAULT_SPRITE_UNIT;
	projectileImage = "";

	std::cout << "Mais um teste!" << std::endl;
	menu.setup(renderer,window,MENU_UNIT);
	sprite.setup(UNIT_DEFAULT_SPRITE_UNIT, SPRITE_TYPE_1);
	//menu.statsMenu();
}

Unit::~Unit(){
//	for (std::vector<Spell*>::iterator it=spellList.begin(); it != spellList.end(); it++){
//		delete (*it);
//	}
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

SDL_Texture* Unit::getTexture(){
	return unit_texture;
}

int Unit::getSpeed(){
	return speed;
}

int Unit::getHp(){
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

	unsigned int actualDamage = rawDamage;

	hp -= actualDamage;
	std::cout << "Unidade " << this << " com " << hp << " de hp apos o combate" << std::endl;
	if (hp <= 0)
		kill();

	BOARD_POINT p;
	p.x = getX();
	p.y = getY();

	setAnimation(Animation(ANIMATION_UNIT_TAKE_DAMAGE,p,p,30,5,6,static_cast<float>(actualDamage)));

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

	BOARD_POINT point,targetPoint;
	point.x = getX();
	point.y = getY();

	targetPoint.x = target->getX();
	targetPoint.y = target->getY();

	Animation a(ANIMATION_UNIT_ATTACK,point,targetPoint,24,6,getFramesAnimation(ANIMATION_UNIT_ATTACK));
	setAnimation(a);

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

//std::vector<Spell *> *Unit::getSpellList(){
//	return &spellList;
//}

unsigned int Unit::getMana(){
	return mana;
}

void Unit::setMana(int amount){
	mana = amount;
	if (mana > manaPool)
		mana = manaPool;
}

void Unit::setAnimation(Animation a){
	animation = a;
}

Animation* Unit::getAnimation(){
	return &animation;
}

bool Unit::isAnimating(){
	if (animation.hasEnded())
		return false;

	return true;
}

std::string Unit::getImage(){
	return image;
}

T_ERROR Unit::statsUpdate()
{
	if (this->menu.textList.size() == 0)
	{
		cout << "Erro configurando o texto no menu da Unidade " << this->getClassName() << endl;
		exit(T_ERROR_TEXT_NOT_INITIALIZED);
	}

	stringstream ss,s;

	s << getHp();
	ss << getMaxHp();

	this->menu.textList[0].setText("Unit: " + this->getClassName());
	this->menu.textList[2].setText("HP: " + s.str() + "/" + ss.str());
	s.str("");
	s << this->getAttackDamage();
	this->menu.textList[3].setText("AD: " + s.str());
	s.str("");
	s << armor;
	this->menu.textList[4].setText("Armor: " + s.str());
	s.str("");
	s << level;
	this->menu.textList[5].setText("Level: " + s.str());
	s.str("");
	s << range;
	this->menu.textList[6].setText("Range: " + s.str());
	s.str("");
	s << this->getActionsPerTurn();
	this->menu.textList[7].setText("Actions: " + s.str());

	return T_SUCCESS;
}

Sprite* Unit::getSprite(){
	return &sprite;
}

std::string Unit::getProjectileImage(){
	return projectileImage;
}
