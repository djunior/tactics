/*
 * Wizard.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "wizard.h"

Wizard::Wizard(T_TEAM t,SDL_Renderer *r, SDL_Window *w) : Unit(t,r,w) {

	hp = WIZARD_HP;
	maxHp = WIZARD_HP;
	attackDamage = WIZARD_DAMAGE;
	armor = WIZARD_ARMOR;
	move = WIZARD_MOVE;
	range = WIZARD_RANGE;
	attackArea = AOE_SHAPE_LINE;
	unitClassName = "Wizard";
//	Fireball *fireball = new Fireball(this);
//	spellList.push_back(fireball);
	mana = WIZARD_MANA_POOL;
	manaPool = WIZARD_MANA_POOL;

	image = WIZARD_SPRITE;

	menu.setImage(WIZARD_SPRITE);
	menu.statsMenu(hp, maxHp, attackDamage, armor, level, move, range, actionPerTurn, mana, manaPool);

	sprite.setup(WIZARD_SPRITE,SPRITE_TYPE_2);
}

Wizard::~Wizard() {
	// TODO Auto-generated destructor stub
}


// Configura um SDL_Rect para apontar um frame da unidade parada.
void Wizard::selectFrameIdle(SDL_Rect *rect){
    rect->w=44;
    rect->h=72;
    rect->x = 30 - (rect->w/2);
    rect->y=10;
}

// Configura um SDL_Rect para apontar um frame da animacao de movimento, baseado no valor de frameIndex
void Wizard::selectFrameMove(int frameIndex, SDL_Rect* rect){

	rect->y = 310;
	rect->h = 71;

	switch(frameIndex){
		case 0:
			rect->w = 28;
			rect->x = 27 - (rect->w/2);
			break;
		case 1:
			rect->w = 35;
			rect->x = 75 - (rect->w/2);
			break;
		case 2:
			rect->w = 46;
			rect->x = 125 - (rect->w/2);
			break;
		case 3:
			rect->w = 40;
			rect->x = 180 - (rect->w/2);
			break;
		case 4:
			rect->w = 30;
			rect->x = 226 - (rect->w/2);
			break;
		case 5:
			rect->w = 38;
			rect->x = 272 - (rect->w/2);
			break;
		case 6:
			rect->w = 45;
			rect->x = 327 - (rect->w/2);
			break;
		case 7:
			rect->w = 38;
			rect->x = 380 - (rect->w/2);
			break;
	};
}

// Configura um SDL_Rect para apontar um frame da animacao de ataque, baseado no valor de frameIndex
void Wizard::selectFrameAttack(int frameIndex, SDL_Rect* rect){
	rect->y = 610;
	rect->h = 70;

	switch(frameIndex){
		case 0:
			rect->w = 37;
			rect->x = 31 - (rect->w/2);
			break;
		case 1:
			rect->w = 37;
			rect->x = 84 - (rect->w/2);
			break;
		case 2:
			rect->w = 58;
			rect->x = 136 - (rect->w/2);
			break;
		case 3:
			rect->w = 39;
			rect->x = 200 - (rect->w/2);
			break;
		case 4:
			rect->w = 34;
			rect->x = 249 - (rect->w/2);
			break;
	};
}

void Wizard::selectFrame(int frameIndex, ANIMATION_TYPE type, SDL_Rect* rect){
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
