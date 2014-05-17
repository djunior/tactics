/*
 * animation.h
 *
 *  Created on: Mar 17, 2014
 *      Author: djunior
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "utils/board_utils.h"
#include <iostream>

enum ANIMATION_TYPE{
	ANIMATION_IDLE,
	ANIMATION_UNIT_MOVE,
	ANIMATION_UNIT_ATTACK
};

typedef enum ANIMATION_TYPE ANIMATION_TYPE;


/*
 * Classe Animation
 *
 * Essa classe � usada para descrever uma anima��o, baseado nos parametros:
 * 		tipo de animacao (movimento, ataque, magias, etc)
 * 		ponto de inicio (x,y),
 * 		ponto de fim (x,y),
 * 		duracao da animacao (em frames),
 * 		numero de repeti��o de frames
 * 		numero de frames
 *
 * 	Considerando que o FPS � fixo em 60 frames/s, a dura��o da anima��o em frames equivale a dura��o da anima��o no tempo
 *	O numero de repeti��o de frames controla a velocidade da anima��o, e quantas vezes a anima��o se repete.
 *
 *	O numero de frames � fixo para cada tipo de anima��o. Uma melhoria � fazer esse numero ser variavel de acordo com o tipo de animacao e a classe que esta animando.
 *	(exemplo, o numero de frames do andar do Knight pode ser diferente do andar do Wizard)
 *
 *	Para uma anima��o de ataque, que so se repete uma vez, os parametros devem ser ajustados de forma que duracao = numero_de_frames * repeticao_de_frames. O numero de
 *	frames eh fixado pelo sprite sheet, e a repeticao_de_frams deve ser escolhido para ajustar a velocidade da animacao.
 *
 */
class Animation {
public:
	BOARD_POINT startPoint, endPoint;
	ANIMATION_TYPE type;
	double currentFrame,duration;
	int repeatFrame;

	Animation(ANIMATION_TYPE,BOARD_POINT, BOARD_POINT,double,int);
	Animation();

	bool hasStarted();
	bool hasEnded();

	virtual ~Animation();

	void debug_showStats();
};

#endif /* ANIMATION_H_ */
