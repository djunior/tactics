#include "mouse.h"

bool hit(SDL_Rect screen_position, int mouse_x, int mouse_y)
{
	if(
		screen_position.x <= mouse_x && 
		screen_position.x + screen_position.h >= mouse_x &&
		screen_position.y <= mouse_y &&
		screen_position.y + screen_position.w >= mouse_y
	)
		return true;
	else
		return false;
};
