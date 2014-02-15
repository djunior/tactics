#ifndef __UNIT_H__
#define __UNIT_H__

class Unit {

protected:
	unsigned int x, y, hp, attackDamage, armor, level, move;
	int speed;
	bool dead;

public:
	bool takeDamage(unsigned int rawDamage);
	void move(int x,int y);
	void setX(unsigned int _x);
	void setY(unsigned int _y);
	unsigned int getX();
	unsigned int getY();
	bool isDead();
	void kill();
};

#endif
