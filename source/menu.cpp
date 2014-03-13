#include "menu.h"

/*===============================
BUTTON
===============================*/


mButton::mButton(SDL_Renderer* renderer, TTF_Font *f)
{
	int w,h;
	bTexture = IMG_LoadTexture(renderer,BUTTON_IMG);
	SDL_QueryTexture(bTexture, NULL, NULL, &w, &h);
	rectBtn.h = h;
	rectBtn.w = w;
	isSelected = false;
	font = f;
	scale = 1;
};

mButton::mButton(SDL_Renderer* renderer, TTF_Font *f,int x, int y)
{
	int w,h;
	bTexture = IMG_LoadTexture(renderer,BUTTON_IMG);
	SDL_QueryTexture(bTexture, NULL, NULL, &w, &h);
	rectBtn.h = h;
	rectBtn.w = w;
	rectBtn.x = x;
	rectBtn.y = y;
	isSelected = false;
	font = f;
	scale = 1;
};

mButton::mButton(SDL_Renderer* renderer, TTF_Font *f,int x, int y, string btnText)
{
	int w,h;
	bTexture = IMG_LoadTexture(renderer,BUTTON_IMG);
	SDL_QueryTexture(bTexture, NULL, NULL, &w, &h);
	rectBtn.h = h;
	rectBtn.w = w;
	rectBtn.x = x;
	rectBtn.y = y;
	text = btnText;
	isSelected = false;
	font = f;
	scale = 1;
};

void mButton::setScale(float mult)
{
	scale = mult;
};

void mButton::setIsSelected(bool sel)
{
	isSelected = sel;
};

void mButton::setPosition(int x,int y)
{
	rectBtn.x = x;
	rectBtn.y = y;
};

void mButton::setColor(SDL_Color color)
{
	text_color = color;
};

void mButton::setText(string btnText)
{
	text = btnText;
};

void mButton::setText(float btnFloat)
{
	ostringstream strStream;   // float to std::string
    strStream << btnFloat;
    string btnText(strStream.str());
	text = btnText;
};

string mButton::getText()
{
	return text;
};

bool mButton::bHit()
{
	if (hit(rectBtn))
	{
		setIsSelected(true);
	}
	else
	{
		setIsSelected(false);
	}
	return hit(rectBtn);
};

void mButton::show(SDL_Renderer* renderer)
{
	SDL_Rect hold;
	hold = rectBtn;
	SDL_Color colorSel = SELECTED;
	SDL_Color colorNotSel = NOT_SELECTED;

	SDL_Rect rectText;
	rectText.x = rectBtn.x + MARGIN_X;
	rectText.y = rectBtn.y + MARGIN_Y;
	rectText = write(renderer,font,text,text_color,rectText,1);

	rectBtn.h = (int)scale*BUTTON_H;
	rectBtn.w = (int)scale*(2*MARGIN_X + rectText.w + 5);

	bHit();

	rectBtn.w = (int)scale*(MARGIN_X + rectText.w);

	if(isSelected == false) 
	{
		setColor(colorNotSel);

		rectTextureBtn.x = 0;
		rectTextureBtn.y = 0;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X + rectText.w;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

		rectBtn.x += (int)scale*(MARGIN_X + rectText.w);
		rectBtn.h = (int)scale*BUTTON_H;
		rectBtn.w = (int)scale*(5 + MARGIN_X);

		rectTextureBtn.x = BUTTON_MAX_W - MARGIN_X;
		rectTextureBtn.y = 2*BUTTON_H + 2*BUTTON_SEPARATION;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);
		
	}
	else
	{
		setColor(colorSel);

		rectTextureBtn.x = 0;
		rectTextureBtn.y = BUTTON_H + BUTTON_SEPARATION;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X + rectText.w;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

		rectBtn.x += (int)scale*(MARGIN_X + rectText.w);
		rectBtn.h = (int)scale*BUTTON_H;
		rectBtn.w = (int)scale*(5 + MARGIN_X);

		rectTextureBtn.x = BUTTON_MAX_W - MARGIN_X;
		rectTextureBtn.y = 3*BUTTON_H + 3*BUTTON_SEPARATION;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);
		
	}
	rectBtn.w = (int)scale*(2*MARGIN_X + rectText.w + 5);
	setPosition(hold.x,hold.y);
	write(renderer,font,text,text_color,rectText,scale);
};

/*===============================
MENU
===============================*/

mWindow::mWindow(TTF_Font *f,SDL_Renderer* rend)
{
	font = f;
	renderer = rend;
};

mWindow::mWindow(TTF_Font *f,SDL_Renderer* rend,SDL_Rect rect, string img)
{
	font = f;
	rectWin = rect;
	renderer = rend;
	image = const_cast<char*>(img.c_str());
};

void mWindow::setIsOpen(bool open)
{
	isOpen = open;
};

void mWindow::setRectWin(SDL_Rect rect)
{
	rectWin = rect;
};

bool mWindow::getIsOpen()
{
	return isOpen;
};

SDL_Rect mWindow::getRectWin()
{
	return rectWin;
};

void mWindow::setImage(string img)
{
	image = const_cast<char*>(img.c_str());
};

void mWindow::setBtnPosition(int x,int y)
{
	btnX = x;
	btnY = y;
};

int mWindow::btnHit()
{
	for (unsigned i=0; i < buttonList.size(); i++)
	{
		if(buttonList[i].bHit())
		{
			return i;
		}
	}
	return -1;
};

void mWindow::addButton(string text)
{
	SDL_Color color = NOT_SELECTED;
	mButton button(renderer,font);
	button.setText(text);
	button.setPosition(btnX,btnY);
	button.setColor(color);
	buttonList.push_back(button);
};

void mWindow::init(int x, int y)
{
	mTexture = IMG_LoadTexture(renderer,image);
	SDL_QueryTexture(mTexture, NULL, NULL, &rectWin.w, &rectWin.h);
	rectWin.x = x;
	rectWin.y = y;
	setIsOpen(true);
};

void mWindow::mainMenu()
{
	setBtnPosition(300,100);
	addButton("Start Game");
	setBtnPosition(300,200);
	addButton("Quit Game");
	setImage(MAIN_MENU_BKG);
	init(0,0);
};

void mWindow::show()
{
	SDL_RenderCopy(renderer, mTexture, NULL, &rectWin);
	for (unsigned i=0; i < buttonList.size(); i++)
	{
		buttonList[i].show(renderer);
	}
};

