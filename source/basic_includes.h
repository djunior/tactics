#ifndef basic_includes_h
#define basic_includes_h

#define WINDOW_MIN_W 800
#define WINDOW_MIN_H 450

#define WINDOW_INITIAL_W 1280
#define WINDOW_INITIAL_H 720
#define WINDOW_PROPORTION WINDOW_INITIAL_W/WINDOW_INITIAL_H

#include <string>
#include <vector>

using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <sstream>

#include <cstdio>
#include <iostream>

#include <ctime>

#include "stdint.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "fps.h"

enum GAME_MANAGER_CONTEXT {
	CONTEXT_IDLE,
	CONTEXT_UNIT_MENU,
	CONTEXT_SPELL_MENU,
	CONTEXT_SPELL_EFFECT,
	CONTEXT_UNIT_COMBAT,
	CONTEXT_UNIT_MOVE,
	CONTEXT_UNIT_SELECT_MOVE,
	CONTEXT_UNIT_SELECT_TARGET,
	CONTEXT_SPELL_SELECT_TARGET,
	CONTEXT_BEGINNING_TURN,
	CONTEXT_ENDING_TURN,
	CONTEXT_BEGINNING_UNIT_TURN,
	CONTEXT_ENDING_UNIT_TURN,
	CONTEXT_END_GAME,
};

typedef enum GAME_MANAGER_CONTEXT GAMEMANAGER_CONTEXT;

enum UNIT_CLASS {
	UNIT_CLASS_WIZARD,
	UNIT_CLASS_KNIGHT,
	UNIT_CLASS_UNIT,
};

typedef enum UNIT_CLASS UNIT_CLASS;

#endif
