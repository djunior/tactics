/*
 * Knight.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "knight.h"

Knight::Knight(T_TEAM t,SDL_Renderer *r, SDL_Window *w)  : Unit (t,r,w) {
	hp = KNIGHT_HP;
	maxHp = KNIGHT_HP;
	attackDamage = KNIGHT_DAMAGE;
	armor = KNIGHT_ARMOR;
	move = KNIGHT_MOVE;
	range = KNIGHT_RANGE;
	unitClassName = "Knight";
	mana = KNIGHT_MANA_POOL;
	manaPool = KNIGHT_MANA_POOL;

	image = KNIGHT_SPRITE;

	menu.setImage(KNIGHT_SPRITE);
	menu.statsMenu(hp, maxHp, attackDamage, armor, level, move, range, actionPerTurn, mana, manaPool);

	sprite.setup(KNIGHT_SPRITE,SPRITE_TYPE_1);
}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

// Configura um SDL_Rect para apontar um frame da unidade parada.
void Knight::selectFrameIdle(SDL_Rect *rect){
    rect->w=44;
    rect->h=72;
    rect->x = 30 - (rect->w/2);
    rect->y=10;
}

// Configura um SDL_Rect para apontar um frame da animacao de movimento, baseado no valor de frameIndex
void Knight::selectFrameMove(int frameIndex, SDL_Rect* rect){

	rect->y = 312;
	rect->h = 70;

	switch(frameIndex){
		case 0:
			rect->w = 25;
			rect->x = 10;
			break;
		case 1:
			rect->w = 32;
			rect->x = 47;
			break;
		case 2:
			rect->w = 44;
			rect->x = 91;
			break;
		case 3:
			rect->w = 36;
			rect->x = 146;
			break;
		case 4:
			rect->w = 25;
			rect->x = 195;
			break;
		case 5:
			rect->w = 32;
			rect->x = 232;
			break;
		case 6:
			rect->w = 43;
			rect->x = 276;
			break;
		case 7:
			rect->w = 37;
			rect->x = 331;
			break;
	};
}

// Configura um SDL_Rect para apontar um frame da animacao de ataque, baseado no valor de frameIndex
void Knight::selectFrameAttack(int frameIndex, SDL_Rect* rect){

	rect->y = 612;
	rect->h = 71;

	switch(frameIndex){
		case 0:
			rect->w = 45;
			rect->x = 32 - (rect->w/2);
			break;
		case 1:
			rect->w = 41;
			rect->x = 87 - (rect->w/2);
			break;
		case 2:
			rect->w = 43;
			rect->x = 136 - (rect->w/2);
			break;
		case 3:
			rect->w = 47;
			rect->x = 192 - (rect->w/2);
			break;
		case 4:
			rect->w = 47;
			rect->x = 251 - (rect->w/2);
			break;
	};
}

void Knight::selectFrame(int frameIndex, ANIMATION_TYPE type, SDL_Rect* rect){
	switch(type){
		case ANIMATION_IDLE:
			selectFrameIdle(rect);
			break;
		case ANIMATION_UNIT_MOVE:
			selectFrameMove(frameIndex,rect);
			break;
		case ANIMATION_UNIT_ATTACK:
			selectFrameAttack(frameIndex, rect);
			break;
		default:
			selectFrameIdle(rect);
			break;
	};
}

void Knight::positionHeadIdle(SDL_Rect*, SDL_Rect*){

}

void Knight::positionHeadMove(int, SDL_Rect*, SDL_Rect*){

}

void Knight::positionHeadAttack(int,SDL_Rect*, SDL_Rect*){

}

void Knight::positionHead(int frameIndex, ANIMATION_TYPE type, SDL_Rect* body, SDL_Rect* head){
	switch(type){
		case ANIMATION_IDLE:
			positionHeadIdle(body,head);
			break;
		case ANIMATION_UNIT_MOVE:
			positionHeadMove(frameIndex,body,head);
			break;
		case ANIMATION_UNIT_ATTACK:
			positionHeadAttack(frameIndex,body,head);
			break;
	};
}
