#ifndef menu_h
#define menu_h

#include "basic_includes.h"
#include "animation.h"
#include "mouse.h"

#include <vector>

#define BUTTON_H 50
#define BUTTON_MAX_W 600
#define BUTTON_SEPARATION 20

#define MARGIN_X 20
#define MARGIN_Y 15

#define SELECTED {255,255,255}
#define NOT_SELECTED {70,70,70}

#define BUTTON_IMG "images\\btn_blue_sprite.gif"
#define MAIN_MENU_BKG "images\\fft_wallpaper.jpg"

class mButton
{
	private:
		bool isSelected;
		SDL_Rect rectBtn;
		SDL_Rect rectTextureBtn;
		SDL_Texture *bTexture;
		string text;
		SDL_Color text_color;
		TTF_Font *font;
		float scale;

	public:
		mButton(SDL_Renderer*, TTF_Font*);
		mButton(SDL_Renderer*, TTF_Font*, int, int);
		mButton(SDL_Renderer*, TTF_Font*, int, int, string);
		void setScale(float);
		void setIsSelected(bool);
		void setPosition(int,int);
		void setColor(SDL_Color);
		void setText(string);
		void setText(float);
		string getText();
		bool bHit();
		void show(SDL_Renderer*);
};

class mWindow
{
	private:
		bool isOpen;
		TTF_Font *font;
		SDL_Renderer* renderer;
		SDL_Rect rectWin;
		const char* image;
		SDL_Texture *mTexture;
		vector<mButton> buttonList;
		int btnX, btnY;

	public:
		mWindow(TTF_Font *,SDL_Renderer*);
		mWindow(TTF_Font *,SDL_Renderer*,SDL_Rect,string);
		void setIsOpen(bool);
		void setRectWin(SDL_Rect);
		void setImage(string);
		void setBtnPosition(int,int);
		bool getIsOpen();
		SDL_Rect getRectWin();
		int btnHit();
		void addButton(string);
		void init(int,int);
		void mainMenu();
		void show();
};

#endif
