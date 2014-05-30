/*
 * gameConfig.cpp
 *
 *  Created on: May 28, 2014
 *      Author: djunior
 */

#include "gameConfig.h"

GameConfig::GameConfig(SDL_Renderer *r, SDL_Window *w) {
	open = false;
	menu.setup(r,w,MENU_GAME_CONFIG);
	menu.gameConfigMenu();

	loadFont(&font);

	teamAUnits = "Unidades do time A: ";
	teamBUnits = "Unidades do time B: ";
}

GameConfig::~GameConfig() {
	// TODO Auto-generated destructor stub
}

void GameConfig::addUnit(T_TEAM team, UNIT_CLASS uClass){
	UNIT_PAIR p = make_pair(team,uClass);
	unitList.push_back(p);

	string strClass = "";

	switch(uClass){
		case UNIT_CLASS_WIZARD:
			strClass = "Wizard";
			break;
		case UNIT_CLASS_KNIGHT:
			strClass = "Knight";
			break;
		default:
			strClass = "Unit";
	}

	if (team == TEAM_A)
		teamAUnits = teamAUnits + " " + strClass + ",";
	else
		teamBUnits = teamBUnits + " " + strClass + ",";
}

void GameConfig::setupDefaultUnitList(){

	addUnit(TEAM_A,UNIT_CLASS_WIZARD);
	addUnit(TEAM_B,UNIT_CLASS_WIZARD);

	addUnit(TEAM_A,UNIT_CLASS_KNIGHT);
	addUnit(TEAM_B,UNIT_CLASS_KNIGHT);

}

bool GameConfig::processMouseEvent(SDL_Event *event){
	bool close = false;

	if (! event->type == SDL_MOUSEBUTTONDOWN)
		return false;

	if (! event->button.button == SDL_BUTTON_LEFT)
		return false;

	switch(menu.btnHit())
	{
		case 0:
			addUnit(TEAM_A,UNIT_CLASS_KNIGHT);
			break;
		case 1:
			addUnit(TEAM_A,UNIT_CLASS_WIZARD);
			break;
		case 2:
			addUnit(TEAM_B,UNIT_CLASS_KNIGHT);
			break;
		case 3:
			addUnit(TEAM_B,UNIT_CLASS_WIZARD);
			break;
		case 4:
			open = false;
			close = true;
			break;
		default:
			break;
	};

	return close;
}

UNIT_LIST_VECTOR* GameConfig::getUnitList(){
	return &unitList;
}

bool GameConfig::isOpen(){
	return open;
}

void GameConfig::start(){
	open = true;
}

void GameConfig::update(SDL_Renderer* r){
	if (! open)
		return;

	menu.show();

	SDL_Rect timeARect;
	timeARect.x = 50;
	timeARect.y = 600;
	timeARect.w = 500;
	timeARect.h = 30;

	SDL_Rect timeBRect;
	timeBRect.x = 50;
	timeBRect.y = 650;
	timeBRect.w = 500;
	timeBRect.h = 30;

	write(r,font,teamAUnits,MENU_BLACK,timeARect,Screen::getXScale(),Screen::getYScale());
	write(r,font,teamBUnits,MENU_BLACK,timeBRect,Screen::getXScale(),Screen::getYScale());

}
