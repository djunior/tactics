#include "menu.h"

/*===============================
TEXT
===============================*/

mText::mText(SDL_Renderer* r,TTF_Font* f,string t,SDL_Color c,float s)
{
	renderer = r;
	font = f;
	text_color = c;
	scale = s;
	text = t;
};

void mText::setScale(float mult)
{
	scale = mult;
};

void mText::setFont(TTF_Font* f)
{
	font = f;
};

void mText::setPosition(int x, int y)
{
	rectText.x = x;
	rectText.y = y;
};

void mText::show()
{
	write(renderer,font,text,text_color,rectText,scale);
};

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

SDL_Rect mButton::getRect()
{
	return rectBtn;
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
	rectText.x = rectBtn.x + MARGIN_X*scale;
	rectText.y = rectBtn.y + MARGIN_Y*scale;

	rectText = simWrite(renderer,font,text,text_color,rectText,1);

	rectBtn.h = (int)BUTTON_H*scale;
	rectBtn.w = (int)(2*MARGIN_X + rectText.w + 5)*scale;

	bHit();

	rectBtn.w = (int)(MARGIN_X + rectText.w)*scale;

	if(isSelected == false) 
	{
		setColor(colorNotSel);

		rectTextureBtn.x = 0;
		rectTextureBtn.y = 0;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X + rectText.w;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

		rectBtn.x += (int)(MARGIN_X + rectText.w)*scale;
		rectBtn.h = (int)BUTTON_H*scale;
		rectBtn.w = (int)(5 + MARGIN_X)*scale;

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

		rectBtn.x += (int)(MARGIN_X + rectText.w)*scale;
		rectBtn.h = (int)BUTTON_H*scale;
		rectBtn.w = (int)(5 + MARGIN_X)*scale;

		rectTextureBtn.x = BUTTON_MAX_W - MARGIN_X;
		rectTextureBtn.y = 3*BUTTON_H + 3*BUTTON_SEPARATION;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);
		
	}
	rectBtn.w = (int)(2*MARGIN_X + rectText.w + 5)*scale;
	setPosition(hold.x,hold.y);
	write(renderer,font,text,text_color,rectText,scale);
};

/*===============================
MENU
===============================*/

mWindow::mWindow(void)
{
	cerr << "Criando Unit.......?" << endl;
	loadFont(&font);

	int wWindow,hWindow;
	SDL_GetWindowSize(window,&wWindow,&hWindow);
	xScale = wWindow*1.0/WINDOW_INITIAL_W;
	yScale = hWindow*1.0/WINDOW_INITIAL_H;
};

mWindow::mWindow(TTF_Font *f,SDL_Renderer* rend, SDL_Window *w)
{
	font = f;
	renderer = rend;
	window = w;

	int wWindow,hWindow;
	SDL_GetWindowSize(window,&wWindow,&hWindow);
	xScale = wWindow*1.0/WINDOW_INITIAL_W;
	yScale = hWindow*1.0/WINDOW_INITIAL_H;

	menu = MAIN;

};

void mWindow::setup(SDL_Renderer* rend, string img, SDL_Window *w, MENU m)
{
	renderer = rend;
	image = const_cast<char*>(img.c_str());
	window = w;
	menu = m;
};

void mWindow::setScale()
{
	int wWindow,hWindow;
	SDL_GetWindowSize(window,&wWindow,&hWindow);
	xScale = wWindow*1.0/WINDOW_INITIAL_W;
	yScale = hWindow*1.0/WINDOW_INITIAL_H;
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

void mWindow::setBtnPosition()
{
	int x,y;
	if (menu == MAIN)
	{
		x = (int)MAIN_BTN_DEFAULT_X*xScale;
		y = (int)MAIN_BTN_DEFAULT_Y*yScale;
		increment = (int)(BUTTON_H + BUTTON_SEPARATION)*yScale;
	}
	if (menu == UNIT)
	{
		x = (int)UNIT_BTN_DEFAULT_X*xScale;
		y = (int)UNIT_BTN_DEFAULT_Y*yScale;
		increment = (int)(BUTTON_H + BUTTON_SEPARATION)*yScale;
	}
	btnX = x;
	btnY = y;

};

void mWindow::setTxtPosition()
{
	int x,y;
	if (menu == MAIN)
	{
		x = (int)MAIN_TXT_DEFAULT_X*xScale;
		y = (int)MAIN_TXT_DEFAULT_Y*yScale;
	}
	if (menu == UNIT)
	{
		x = (int)UNIT_TXT_DEFAULT_X*xScale;
		y = (int)UNIT_TXT_DEFAULT_Y*yScale;
		//increment = (int)(BUTTON_H + BUTTON_SEPARATION)*yScale;
	}
	txtX = x;
	txtY = y;

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

void mWindow::addText(string text)
{
	SDL_Color color = NOT_SELECTED;
	mText textLine(renderer,font,text,color,yScale);
	textLine.setPosition(txtX,txtY);
	textList.push_back(textLine);
}

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
	addText("TACTICS");
	addButton("Start Game");
	addButton("Quit Game");
	setImage(MAIN_MENU_BKG);
	setScale();
	menu = MAIN;
	setBtnPosition();
	init(0,0);
};

void mWindow::statsMenu()
{
	addText("Testando Boladamente");
	setTxtPosition();
	init(0,0);
};

void mWindow::show()
{
	if (getIsOpen())
	{
		setScale();
		setBtnPosition();
		setTxtPosition();

		int xB,yB;
		int xT,yT;

		xB = btnX;
		yB = btnY;

		xT = txtX;
		yT = txtY;

		if(menu == MAIN)
		{
			TTF_Font *title;
			loadTitle(&title);

			SDL_RenderCopy(renderer, mTexture, NULL, NULL);

			textList[0].setFont(title);
			textList[0].setPosition(xT,yT);
			textList[0].setScale(yScale);
			textList[0].show();

			for (unsigned i=0; i < buttonList.size(); i++)
			{
				buttonList[i].setPosition(xB,yB + increment*i);
				buttonList[i].setScale(yScale);
				buttonList[i].show(renderer);
			}
		}
		if(menu == UNIT)
		{
			textList[0].setPosition(xT,yT);
			textList[0].setScale(yScale);
			textList[0].show();
		}
	}
};

