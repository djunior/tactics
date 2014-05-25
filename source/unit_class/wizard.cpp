/*
 * Wizard.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "wizard.h"

Wizard::Wizard(T_TEAM t,SDL_Renderer *r, SDL_Window *w) : Unit(t,r,w) {

	initUnitStats();

	menu.setImage(WIZARD_SPRITE);
	menu.statsMenu(hp, maxHp, attackDamage, armor, level, move, range, actionPerTurn, mana, manaPool);

	sprite.setup(WIZARD_SPRITE,SPRITE_TYPE_2);
}

Wizard::~Wizard() {
	// TODO Auto-generated destructor stub
}

void Wizard::initUnitStats(){
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
	projectileImage = WIZARD_PROJECTILE_SPRITE;
}

// Configura um SDL_Rect para apontar um frame da unidade parada.
void Wizard::selectFrameIdle(SDL_Rect *rect){
	if (isDead() == true){
		rect->x = 664;
		rect->y = 725;
		rect->w = 136;
		rect->h = 120;
	} else {
		rect->x = 299;
		rect->y = 0;
		rect->w = 136;
		rect->h = 120;
	}
}

// Configura um SDL_Rect para apontar um frame da animacao de movimento, baseado no valor de frameIndex
void Wizard::selectFrameMove(int frameIndex, SDL_Rect* rect){

	rect->w = 136;
	rect->h = 119;

	if (frameIndex == 0){
		rect->x = 839;
		rect->y = 0;
	} else {
		rect->x = 119 + (frameIndex-1)*(rect->w + 44);
		rect->y = 179;
	}
}

// Configura um SDL_Rect para apontar um frame da animacao de ataque, baseado no valor de frameIndex
void Wizard::selectFrameAttack(int frameIndex, SDL_Rect* rect){
	rect->w = 136;
	rect->h = 145;
	rect->x = 119 + (frameIndex)*(rect->w+44);
	rect->y = 516;
}

void Wizard::selectFrame(int frameIndex, ANIMATION_TYPE type, SDL_Rect* rect){
	switch(type){
		case ANIMATION_IDLE:
			selectFrameIdle(rect);
			break;
		case ANIMATION_UNIT_MOVE:
			selectFrameMove(frameIndex, rect);
			break;
		case ANIMATION_UNIT_ATTACK:
			selectFrameAttack(frameIndex, rect);
			break;
		default:
			selectFrameIdle(rect);
			break;
	};
}


void Wizard::positionHeadIdle(SDL_Rect* body, SDL_Rect* head){
	head->x = body->x + (body->w - head->w)/2;
	head->y = body->y - head->h*4/5;
}

void Wizard::positionHeadMove(int frameIndex, SDL_Rect* body, SDL_Rect* head){
	positionHeadIdle(body,head);
}

void Wizard::positionHeadAttack(int frameIndex ,SDL_Rect* body, SDL_Rect* head){
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

void Wizard::positionHead(int frameIndex, ANIMATION_TYPE type, SDL_Rect* body, SDL_Rect* head){
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

int Wizard::getFramesAnimation(ANIMATION_TYPE type){
	switch(type){
		case ANIMATION_IDLE:
			return 1;
		case ANIMATION_UNIT_MOVE:
			return 5;
		case ANIMATION_UNIT_ATTACK:
			return 4;
		default:
			return 1;
	};
	return 1;
}

