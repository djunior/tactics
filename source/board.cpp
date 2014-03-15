/*
 * Board.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: djunior
 */

#include "board.h"
#include "utils/t_error.h"

Board::Board(int width, int length){
	// Por enquanto, o tamanho do tabuleiro sera fixo em 8 x 8
	maxBoardX = width;
	maxBoardY = length;

	for (int x = 0; x < maxBoardX; x++){
		for (int y = 0; y < maxBoardY; y++){
			boardMap[y][x] = 0;
		}
	}
}

T_ERROR Board::addUnit(Unit * u, unsigned int x, unsigned int y){
	if (!u)
		return T_ERROR_INVALID_UNIT;

	if ((x > maxBoardX) || (y > maxBoardY))
		return T_ERROR_OUT_OF_BOUNDS;

	if (boardMap[y][x] != 0)
		return T_ERROR_INVALID_LOCATION;

	boardMap[y][x] = u;

	u->setOrigin(x,y);

	return T_SUCCESS;
}

T_ERROR Board::addUnit(Unit *u){
	std::cout << "Board::addUnit Adicionando unidade " << u << std::endl;
	unsigned int ix = 0, iy = 0;
	std::cout << "MAX BOARD Y: " << maxBoardY << std::endl;
	if (u->getTeam() == TEAM_B)
		ix = maxBoardX-1;

	while(boardMap[iy][ix] != 0) {
		iy++;
		if (iy == maxBoardY) {
			iy = 0;
			if (u->getTeam() == TEAM_A)
				ix++;
			else
				ix--;
		}
		if (ix == maxBoardX)
			return T_ERROR_MAP_FULL;
		else if(ix < 0)
			return T_ERROR_MAP_FULL;
	};

	addUnit(u,ix,iy);

	return T_SUCCESS;
}

T_ERROR Board::moveUnit(Unit* u, unsigned int x, unsigned int y){
	if (!u)
		return T_ERROR_INVALID_UNIT;

	if ((x > maxBoardX) || (y > maxBoardY))
		return T_ERROR_OUT_OF_BOUNDS;
	std::cout << "BoardMap na posicao (" << y << "," << x << ") = " << boardMap[y][x] << std::endl;

	if (boardMap[y][x] != 0)
		return T_ERROR_INVALID_LOCATION;

	if (boardMap[u->getY()][u->getX()] != u)
		return T_ERROR_INVALID_UNIT;

	boardMap[u->getY()][u->getX()] = 0;
	boardMap[y][x] = u;

	u->setOrigin(x,y);

	return T_SUCCESS;
}

T_ERROR Board::checkUnitsInVicinity(Unit *u, unsigned int range, vector<Unit*> *targetList){
	if (u == 0)
		return T_ERROR_INVALID_UNIT;

	for (int y=u->getY()-range; y <= u->getY()+range; y++) {
		if (y >=0 && y < maxBoardY) {
			for (int x=u->getX()-range; x <= u->getX()+range; x++) {
				if (x >= 0 && y < maxBoardX) {
					if (x != u->getX() && y != u->getY() && boardMap[y][x] != 0){
						targetList->push_back(boardMap[y][x]);
					}
				}
			}
		}
	}

	return T_SUCCESS;
}

Unit* Board::getUnitAt(unsigned int x, unsigned int y){
	if (x > maxBoardX || y > maxBoardY)
		return 0;

	// Isso vai ser ou uma unidade ou 0
	return boardMap[y][x];
}

T_ERROR Board::removeUnit(Unit * unit){
	if (unit == 0)
		return T_ERROR_INVALID_UNIT;

	if (unit->getX() > maxBoardX || unit->getY() > maxBoardY)
		return T_ERROR_OUT_OF_BOUNDS;

	if (boardMap[unit->getY()][unit->getX()] == 0 || boardMap[unit->getY()][unit->getX()] != unit)
		return T_ERROR_INVALID_UNIT;

	boardMap[unit->getY()][unit->getX()] = 0;

	return T_SUCCESS;
}

T_ERROR Board::checkUnitsInAOE(int x, int y, int range,BOARD_AXIS axis, AOE_SHAPE shape, vector<Unit *> *targetList){
	std::cout << "Board::checkUnitsInAOE: x=" << x << " y=" << y << " range=" << range << std::endl;

	if (x < 0 || x > maxBoardX || y < 0 || y > maxBoardY)
		return T_ERROR_OUT_OF_BOUNDS;

	if (shape == AOE_SHAPE_POINT) {

		if (boardMap[y][x] == 0)
			return T_ERROR_INVALID_UNIT;

		targetList->push_back(boardMap[y][x]);

	} else if (shape == AOE_SHAPE_LINE) {

		if (axis == BOARD_AXIS_X_MINUS)
			x-= (range-1);
		else if (axis == BOARD_AXIS_Y_MINUS)
			y-= (range-1);

		if ( x < 0)
			x = 0;

		if (y < 0)
			y = 0;

		int finalX = x+range;
		int finalY = y+range;

		if (finalX > maxBoardX)
			finalX = maxBoardX;

		if (finalY > maxBoardY)
			finalY = maxBoardY;


		if (axis == BOARD_AXIS_X || axis == BOARD_AXIS_X_MINUS) {
			for (int i=x;i<finalX;i++) {
				std::cout << "TESTANDO POSICAO (" << i << "," << y << ")" << std::endl;
				if (boardMap[y][i] != 0) {
					std::cout << "(" << i << "," << y << ") = " << boardMap[y][i] << std::endl;
					targetList->push_back(boardMap[y][i]);
				}
			}
		} else if (axis == BOARD_AXIS_Y || axis == BOARD_AXIS_Y_MINUS) {
			for (int i=y;i<finalY;i++) {
				if (boardMap[i][x] != 0){
					targetList->push_back(boardMap[i][x]);
				}
			}
		}

		if (axis == BOARD_AXIS_X_MINUS || axis == BOARD_AXIS_Y_MINUS)
			std::reverse(targetList->begin(),targetList->end());
	}

	return T_SUCCESS;
}

unsigned int Board::getMaxBoardX(){
	return maxBoardX;
}

unsigned int Board::getMaxBoardY(){
	return maxBoardY;
}

void Board::debug_showMap(){
	std::cout << "Dump do tabuleiro:" << std::endl;
	for (int y = 0;y < maxBoardY; y++){
		for (int x = 0; x < maxBoardX; x++){

			if (boardMap[y][x] == 0)
				std::cout << " . ";
			else
				std::cout << " U ";
		}
		std::cout << std::endl;
	}
}

