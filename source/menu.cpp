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

void mButton::show(SDL_Renderer* renderer)
{
	SDL_Rect hold;
	hold = rectBtn;

	SDL_Rect rectText;
	rectText.x = rectBtn.x + MARGIN_X;
	rectText.y = rectBtn.y + MARGIN_Y;
	rectText = write(renderer,font,text,text_color,rectText,1);

	if(isSelected == false)
	{
		rectBtn.h = BUTTON_H;
		rectBtn.w = MARGIN_X + rectText.w;

		rectTextureBtn.x = 0;
		rectTextureBtn.y = 0;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X + rectText.w;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

		rectBtn.x += MARGIN_X + rectText.w;
		rectBtn.h = BUTTON_H;
		rectBtn.w = 5 + MARGIN_X;

		rectTextureBtn.x = BUTTON_MAX_W -MARGIN_X;
		rectTextureBtn.y = 2*BUTTON_H + 2*BUTTON_SEPARATION;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);
		
	}
	else
	{
		SDL_RenderCopy(renderer, bTexture, NULL, &rectBtn);
	}
	setPosition(hold.x,hold.y);
	write(renderer,font,text,text_color,rectText,1);
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
	rectWin = rectWin;
};

void mWindow::setImage(string img)
{
	image = const_cast<char*>(img.c_str());
};

bool mWindow::getIsOpen()
{
	return isOpen;
};

SDL_Rect mWindow::getRectWin()
{
	return rectWin;
};

void mWindow::addButton(string text)
{
	SDL_Color color = WHITE;
	mButton button(renderer,font);
	button.setText(text);
	button.setPosition(100,100);
	button.setColor(color);
	buttonList.push_back(button);
};

void mWindow::init(int x, int y)
{
	mTexture = IMG_LoadTexture(renderer,image);
	SDL_QueryTexture(mTexture, NULL, NULL, &rectWin.w, &rectWin.h);
	rectWin.x = x;
	rectWin.y = y;
};

void mWindow::mainMenu()
{
	addButton("Teste");
	setImage(MAIN_MENU_BKG);
	init(0,0);
};

void mWindow::show()
{
	SDL_RenderCopy(renderer, mTexture, NULL, &rectWin);
	/*for (vector<mButton>::iterator it=buttonList.begin(); it != buttonList.end(); it++){
		(*it).show(renderer);
	}*/
	buttonList[0].show(renderer);
};

