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
    rect->x = 181;
    rect->y = 3;
    rect->w = 136;
    rect->h = 123;
}

// Configura um SDL_Rect para apontar um frame da animacao de movimento, baseado no valor de frameIndex
void Knight::selectFrameMove(int frameIndex, SDL_Rect* rect){

	rect->w = 136;
	rect->h = 111;

	rect->x = 0 + (44 + rect->w)*(frameIndex);
	rect->y = 188;

}

// Configura um SDL_Rect para apontar um frame da animacao de ataque, baseado no valor de frameIndex
void Knight::selectFrameAttack(int frameIndex, SDL_Rect* rect){

//	if (frameIndex < 6){
//		rect->w = 136;
//		rect->h = 107;
//
//		rect->x = (44 + rect->w)*(frameIndex);
//		rect->y = 372;
//
//	} else {
		rect->w = 136;
		rect->h = 122;

		rect->x = 181 + (44 + rect->w)*(frameIndex);
		rect->y = 733;
//	}

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

void Knight::positionHeadIdle(SDL_Rect* body, SDL_Rect* head){
	head->x = body->x + (body->w - head->w)/2;
	head->y = body->y - head->h*4/5;
}

void Knight::positionHeadMove(int frameIndex, SDL_Rect* body, SDL_Rect* head){
	positionHeadIdle(body,head);
}

void Knight::positionHeadAttack(int frameIndex ,SDL_Rect* body, SDL_Rect* head){
	switch(frameIndex){
		case 0:
			head->x = body->x + (body->w - head->w)/2;
			head->y = body->y - head->h/4;
			break;
		case 1:
			head->x = body->x + (body->w - head->w)/2;
			head->y = body->y - head->h/4;
			break;
		case 2:
			head->x = body->x + (body->w - head->w)/2;
			head->y = body->y - head->h/4;
			break;
		case 3:
			head->x = body->x + (body->w - head->w)/2;
			head->y = body->y - head->h/4;
			break;
		case 4:
			head->x = body->x + (body->w - head->w)/2;
			head->y = body->y - head->h/4;
			break;
	};
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

int Knight::getFramesAnimation(ANIMATION_TYPE type){
	switch(type){
		case ANIMATION_IDLE:
			return 1;
		case ANIMATION_UNIT_MOVE:
			return 6;
		case ANIMATION_UNIT_ATTACK:
			return 4;
		default:
			return 1;
	};

	return 1;
}
