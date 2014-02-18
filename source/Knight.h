/*
 * Knight.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "Unit.h"
#include "utils/t_team.h"

#define KNIGHT_HP 80
#define KNIGHT_DAMAGE 20
#define KNIGHT_RANGE 1
#define KNIGHT_MOVE 2
#define KNIGHT_ARMOR 5

class Knight : public Unit {
public:
	Knight(T_TEAM t);
	virtual ~Knight();
};

#endif /* KNIGHT_H_ */
