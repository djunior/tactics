#ifndef menu_h
#define menu_h

#include "basic_includes.h"
#include "animation.h"

class mWindow
{
	private:
		bool isOpen;
		TTF_Font *font;
		SDL_Rect rectWin;
	public:
		mWindow(TTF_Font *);
		mWindow(TTF_Font *,SDL_Rect);
		void setIsOpen(bool);
		void setRectWin(SDL_Rect);
		bool getIsOpen();
		SDL_Rect getRectWin();
};

#endif
