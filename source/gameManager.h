#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "board.h"
#include <vector>
#include <map>
#include "utils/t_team.h"

#define GAMEMANAGER_INITIAL_TURN 0;

class GameManager{
private:
	vector<Unit *> unitList;
	std::map<std::string,Spell *> spellMap;
	Board* board;
	unsigned int turn;
	int teamABodyCount, teamBBodyCount;

	void cleanup();
	int getOtherTeamBodyCount(T_TEAM team);

public:
	GameManager(Board* newBoard);
	~GameManager();
	void createUnit(string unitClass,T_TEAM team);
	void startTurn();
	void startGame();
	void endGame();
	void notifyDeath(T_TEAM team, int casualties);
	unsigned int getTurn();
};

#endif
