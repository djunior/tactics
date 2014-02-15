#ifndef __UNIT_H__
#define __UNIT_H__

#include "utils/t_team.h"

#define UNIT_DEFAULT_HP 50
#define UNIT_DEFAULT_DAMAGE 10
#define UNIT_DEFAULT_ARMOR 1
#define UNIT_DEFAULT_LEVEL 1
#define UNIT_DEFAULT_MOVE 1
#define UNIT_DEFAULT_SPEED 1
#define UNIT_DEFAULT_RANGE 1

class Unit {

protected:
	unsigned int x, y, hp, attackDamage, armor, level, move, range;
	int speed;
	bool dead;
	T_TEAM team;

public:
	Unit (T_TEAM t);
	bool takeDamage(unsigned int rawDamage);
	void setX(unsigned int _x);
	void setY(unsigned int _y);
	void setOrigin(unsigned int _x, unsigned int _y);
	unsigned int getX();
	unsigned int getY();
	T_TEAM getTeam();
	bool isDead();
	void kill();
	int getSpeed();
	unsigned int getMove();
	unsigned int getHp();
	unsigned int getRange();
	unsigned int attack();
};

#endif
