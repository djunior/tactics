#ifndef __UNIT_H__
#define __UNIT_H__

#include "basic_includes.h"
#include "utils/t_team.h"
#include <iostream>
#include <vector>
#include "utils/t_error.h"
#include "utils/board_utils.h"

#define UNIT_DEFAULT_HP 1
#define UNIT_DEFAULT_DAMAGE 0
#define UNIT_DEFAULT_ARMOR 1
#define UNIT_DEFAULT_LEVEL 1
#define UNIT_DEFAULT_MOVE 1
#define UNIT_DEFAULT_SPEED 1
#define UNIT_DEFAULT_RANGE 1
#define UNIT_DEFAULT_ACTION_PER_TURN 1
#define UNIT_DEFAULT_MANA_POOL 0

#define UNIT_DEFAULT_SPRITE_UNIT "images\\char_lanca.png"

class Spell;

class Unit {

protected:
	const char* image;
	SDL_Texture* unit_texture;
	unsigned int x, y, hp, maxHp, attackDamage, armor, level, move, range, actionPerTurn, mana, manaPool;
	std::string unitClassName;
	int speed;
	bool dead;
	T_TEAM team;
	AOE_SHAPE attackArea;
	std::vector<Spell *> spellList;

public:
	Unit (T_TEAM t,SDL_Renderer *renderer);
	virtual ~Unit();
	bool takeDamage(unsigned int rawDamage);
	void setX(unsigned int _x);
	void setY(unsigned int _y);
	void setOrigin(unsigned int _x, unsigned int _y);
	unsigned int getX();
	unsigned int getY();
	T_TEAM getTeam();
	SDL_Texture* getTexture();
	bool isDead();
	void kill();
	int getSpeed();
	unsigned int getMove();
	unsigned int getHp();
	unsigned int getMaxHp();
	unsigned int getRange();
	unsigned int getAttackDamage();
	unsigned int getActionsPerTurn();
	unsigned int getMana();
	void setMana(int amount);
	AOE_SHAPE getAttackArea();
	std::string getClassName();
	int combat(std::vector<Unit *> *targetList);
	T_ERROR combat(std::vector<Unit *> *targetList, int *bodyCount);
	void debug_showStats();
	void debug_showStats(bool verbose);
	std::vector<Spell *> *getSpellList();
};

#endif
