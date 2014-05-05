/*
 * sprite.cpp
 *
 *  Created on: May 4, 2014
 *      Author: djunior
 */

#include "sprite.h"

Sprite::Sprite(){
	imageUri = "";
	type = SPRITE_TYPE_1;
}

Sprite::Sprite(std::string s, SPRITE_TYPE t) {
	setup(s,t);
}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

void Sprite::setup(std::string s, SPRITE_TYPE t){
	imageUri = s;
	type = t;
}

std::string Sprite::getImageURI(){
	return imageUri;
}

SPRITE_TYPE Sprite::getType(){
	return type;
}

