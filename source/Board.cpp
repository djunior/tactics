/*
 * Board.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "Board.h"
#include "utils/t_error.h"

Board::Board(int width, int length){
	// Por enquanto, o tamanho do tabuleiro sera fixo em 8 x 8
	maxBoardWidth = width;
	maxBoardLength = length;

	for (int x = 0; x < maxBoardWidth; x++){
		for (int y = 0; y < maxBoardLength; y++){
			boardMap[x][y] = 0;
		}
	}
}

T_ERROR Board::addUnit(Unit * u, unsigned int x, unsigned int y){
	if (!u)
		return T_ERROR_INVALID_UNIT;

	if ((x > maxBoardWidth) || (y > maxBoardLength))
		return T_ERROR_OUT_OF_BOUNDS;

	if (boardMap[x][y] != 0)
		return T_ERROR_INVALID_LOCATION;

	boardMap[x][y] = u;

	u->setOrigin(x,y);

	return T_SUCCESS;
}

T_ERROR Board::addUnit(Unit *u){
	std::cout << "Board::addUnit Adicionando unidade " << u << std::endl;
	unsigned int ix = 0, iy = 0;

	while(boardMap[ix][iy] != 0) {
		ix++;
		if (ix == maxBoardWidth) {
			ix = 0;
			iy++;
		}
		if (iy == maxBoardLength)
			return T_ERROR_MAP_FULL;

	};

	addUnit(u,ix,iy);

	return T_SUCCESS;
}

T_ERROR Board::moveUnit(Unit* u, unsigned int x, unsigned int y){
	if (!u)
		return T_ERROR_INVALID_UNIT;

	if ((x > maxBoardWidth) || (y > maxBoardLength))
		return T_ERROR_OUT_OF_BOUNDS;
	std::cout << "BoardMap na posicao (" << x << "," << y << ") = " << boardMap[x][y] << std::endl;

	if (boardMap[x][y] != 0)
		return T_ERROR_INVALID_LOCATION;

	if (boardMap[u->getX()][u->getY()] != u)
		return T_ERROR_INVALID_UNIT;

	boardMap[u->getX()][u->getY()] = 0;
	boardMap[x][y] = u;

	u->setOrigin(x,y);

	return T_SUCCESS;
}

T_ERROR Board::checkUnitsInVicinity(Unit *u, unsigned int range, vector<Unit*> *targetList){
	if (u == 0)
		return T_ERROR_INVALID_UNIT;

	for (int x=u->getX()-range; x <= u->getX()+range; x++) {
		if (x >=0 && x < maxBoardWidth) {
			for (int y=u->getY()-range; y <= u->getY()+range; y++) {
				if (y >= 0 && y < maxBoardLength) {
					if (x != u->getX() && y != u->getY() && boardMap[x][y] != 0){
						targetList->push_back(boardMap[x][y]);
					}
				}
			}
		}
	}

	return T_SUCCESS;
}

Unit* Board::getUnitAt(unsigned int x, unsigned int y){
	if (x > maxBoardWidth || y > maxBoardLength)
		return 0;

	// Isso vai ser ou uma unidade ou 0
	return boardMap[x][y];
}

T_ERROR Board::removeUnit(Unit * unit){
	if (unit == 0)
		return T_ERROR_INVALID_UNIT;

	if (unit->getX() > maxBoardWidth || unit->getY() > maxBoardLength)
		return T_ERROR_OUT_OF_BOUNDS;

	if (boardMap[unit->getX()][unit->getY()] == 0 || boardMap[unit->getX()][unit->getY()] != unit)
		return T_ERROR_INVALID_UNIT;

	boardMap[unit->getX()][unit->getY()] = 0;

	return T_SUCCESS;
}

T_ERROR Board::checkUnitsInAOE(int x, int y, int range,BOARD_AXIS axis, AOE_SHAPE shape, vector<Unit *> *targetList){

	if (shape == AOE_SHAPE_LINE) {

		if (axis == BOARD_AXIS_X_MINUS)
			x-=range;
		else if (axis == BOARD_AXIS_Y_MINUS)
			y-=range;

		if (axis == BOARD_AXIS_X || axis == BOARD_AXIS_X_MINUS) {
			for (int i=x;i<x+range;i++) {
				if (boardMap[i][y] != 0)
					targetList->push_back(boardMap[i][y]);
			}
		} else if (axis == BOARD_AXIS_Y || axis == BOARD_AXIS_Y_MINUS) {
			for (int i=y;i<y+range;i++) {
				if (boardMap[x][i] != 0)
					targetList->push_back(boardMap[x][i]);
			}
		}

		if (axis == BOARD_AXIS_X_MINUS || axis == BOARD_AXIS_Y_MINUS)
			std::reverse(targetList->begin(),targetList->end());
	}

	return T_SUCCESS;
}

void Board::debug_showMap(){
	std::cout << "Dump do tabuleiro:" << std::endl;
	for (int x = 0; x < maxBoardWidth; x++){
		for (int y = 0; y < maxBoardLength; y++){

			if (boardMap[x][y] == 0)
				std::cout << " . ";
			else
				std::cout << " U ";
		}
		std::cout << std::endl;
	}
}
