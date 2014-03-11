#include "menu.h"

mWindow::mWindow(TTF_Font *f)
{
	font = f;
};

mWindow::mWindow(TTF_Font *f,SDL_Rect rect)
{
	font = f;
	rectWin = rect;
};

void mWindow::setIsOpen(bool open)
{
	isOpen = open;
};
void mWindow::setRectWin(SDL_Rect rect)
{
	rectWin = rectWin;
};
bool mWindow::getIsOpen()
{
	return isOpen;
};
SDL_Rect mWindow::getRectWin()
{
	return rectWin;
};
