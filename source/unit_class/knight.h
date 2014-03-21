/*
 * Knight.h
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "../unit.h"
#include "../utils/t_team.h"

#define KNIGHT_HP 80
#define KNIGHT_DAMAGE 20
#define KNIGHT_RANGE 1
#define KNIGHT_MOVE 2
#define KNIGHT_ARMOR 5
#define KNIGHT_MANA_POOL 10

#define KNIGHT_SPRITE "images\\char_lanca.png"

class Knight : public Unit {
public:
	Knight(T_TEAM t,SDL_Renderer *r, SDL_Window *w);
	virtual ~Knight();
};

#endif /* KNIGHT_H_ */
