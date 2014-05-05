/*
 * sprite.h
 *
 *  Created on: May 4, 2014
 *      Author: djunior
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <iostream>

enum SPRITE_TYPE{
	SPRITE_TYPE_1,
	SPRITE_TYPE_2
};

typedef enum SPRITE_TYPE SPRITE_TYPE;

class Sprite {
private:
	std::string imageUri;
	SPRITE_TYPE type;

public:
	Sprite();
	Sprite(std::string, SPRITE_TYPE);
	virtual ~Sprite();

	void setup(std::string, SPRITE_TYPE);
	std::string getImageURI();
	SPRITE_TYPE getType();
};

#endif /* SPRITE_H_ */
