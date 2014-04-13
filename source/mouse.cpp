#include "mouse.h"

bool hit(SDL_Rect screen_position)
{
	int mouse_x,mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);

	if(
		screen_position.x <= mouse_x && 
		screen_position.x + screen_position.w >= mouse_x &&
		screen_position.y <= mouse_y &&
		screen_position.y + screen_position.h >= mouse_y
	)
		return true;
	else
		return false;
};

/*BOARD_AOE mouseBoardPosition()
{
	return BOARD_AOE area;
}*/
