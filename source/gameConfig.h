/*
 * gameConfig.h
 *
 *  Created on: May 28, 2014
 *      Author: djunior
 */

#ifndef GAMECONFIG_H_
#define GAMECONFIG_H_

#include "basic_includes.h"
#include "utils/t_team.h"
#include "menu.h"
#include "drawFunctions.h"

typedef pair<T_TEAM,UNIT_CLASS> UNIT_PAIR;
typedef vector<UNIT_PAIR> UNIT_LIST_VECTOR;

class GameConfig {
private:
	UNIT_LIST_VECTOR unitList;
	mWindow menu;
	bool open;
	TTF_Font* font;
	string teamAUnits,teamBUnits;

	void addUnit(T_TEAM,UNIT_CLASS);

public:
	GameConfig(SDL_Renderer *r, SDL_Window *w);
	virtual ~GameConfig();
	bool processMouseEvent(SDL_Event *event);
	UNIT_LIST_VECTOR* getUnitList();
	bool isOpen();
	void start();
	void setupDefaultUnitList();
	void update(SDL_Renderer* r);
};

#endif /* GAMECONFIG_H_ */
