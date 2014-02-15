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

T_ERROR Board::moveUnit(Unit* u, unsigned int x, unsigned int y){
	if (!u)
		return T_ERROR_INVALID_UNIT;

	if ((x > maxBoardWidth) || (y > maxBoardLength))
		return T_ERROR_OUT_OF_BOUNDS;

	if (boardMap[x][y] != 0)
		return T_ERROR_INVALID_LOCATION;


	boardMap[u->getX()][u->getY()] = 0;
	boardMap[x][y] = u;

	u->setOrigin(x,y);

	return T_SUCCESS;
}

vector<Unit*> Board::checkUnitsInVicinity(Unit *u, unsigned int range){

	vector<Unit*> unitList;

	for (int x=u->getX()-range; x <= u->getX()+range; x++) {
		if (x >=0 && x < maxBoardWidth) {
			for (int y=u->getY()-range; y <= u->getY()+range; y++) {
				if (y >= 0 && y < maxBoardLength) {
					if (x != u->getX() && y != u->getY() && boardMap[x][y] != 0){
						unitList.push_back(boardMap[x][y]);
					}
				}
			}
		}
	}

	return unitList;
}
