#include "menu.h"

/*===============================
TEXT
===============================*/

mText::mText(SDL_Renderer* r,TTF_Font* f,string t,SDL_Color c,float s)
{
	renderer = r;
	font = f;
	text_color = c;
	xScale = s;
	yScale = s;
	text = t;
};

void mText::setScale(float x, float y)
{
	xScale = x;
	yScale = y;
};

void mText::setFont(TTF_Font* f)
{
	font = f;
};

void mText::setText(string t)
{
	text = t;
}

void mText::setColor(SDL_Color c)
{
	text_color = c;
};

void mText::setPosition(int x, int y)
{
	rectText.x = x;
	rectText.y = y;
};

void mText::show()
{
	write(renderer,font,text,text_color,rectText,xScale,yScale);
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
	isEnabled = true;
	font = f;
	xScale = 1;
	yScale = 1;
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
	isEnabled = true;
	font = f;
	xScale = 1;
	yScale = 1;
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
	isEnabled = true;
	font = f;
	xScale = 1;
	yScale = 1;
};

void mButton::enable(){
	isEnabled = true;
}

void mButton::disable(){
	isEnabled = false;
}

void mButton::setScale(float x, float y)
{
	xScale = x;
	yScale = y;
};

void mButton::setFont()
{
	font = TTF_OpenFont("images\\FinalFrontier.ttf", 12);
    if (font == NULL)
    {
	    cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
	    TTF_Quit();
	    SDL_Quit();
	    exit(1);
    }
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
	return (isEnabled && hit(rectBtn));
};

void mButton::show(SDL_Renderer* renderer)
{
	SDL_Rect hold;
	hold = rectBtn;
	SDL_Color colorSel = SELECTED;
	SDL_Color colorNotSel = NOT_SELECTED;

	SDL_Rect rectText;
	rectText.x = static_cast<int>(rectBtn.x + MARGIN_X*xScale);
	rectText.y = static_cast<int>(rectBtn.y + MARGIN_Y*yScale);

	rectText = simWrite(renderer,font,text,text_color,rectText,1);

	rectBtn.h = static_cast<int>(BUTTON_H*yScale);
	rectBtn.w = static_cast<int>((2*MARGIN_X + rectText.w + 5)*xScale);

	bHit();

	rectBtn.w = static_cast<int>((MARGIN_X + rectText.w)*xScale);

	if (isEnabled == false) {

		setColor(colorNotSel);

		rectTextureBtn.x = 0;
		rectTextureBtn.y = 0;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X + rectText.w;

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

		rectBtn.x += static_cast<int>((MARGIN_X + rectText.w)*xScale);
		rectBtn.h = static_cast<int>(BUTTON_H*yScale);
		rectBtn.w = static_cast<int>((5 + MARGIN_X)*xScale);

		rectTextureBtn.x = BUTTON_MAX_W - MARGIN_X;
		rectTextureBtn.y = 2*BUTTON_H + 2*BUTTON_SEPARATION;
		rectTextureBtn.h = BUTTON_H;
		rectTextureBtn.w = MARGIN_X;

		SDL_SetTextureColorMod(bTexture,50,50,50);

		SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

	} else {
		SDL_SetTextureColorMod(bTexture,255,255,255);
		if(isSelected == false)
		{
			setColor(colorNotSel);

			rectTextureBtn.x = 0;
			rectTextureBtn.y = 0;
			rectTextureBtn.h = BUTTON_H;
			rectTextureBtn.w = MARGIN_X + rectText.w;

			SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

			rectBtn.x += static_cast<int>((MARGIN_X + rectText.w)*xScale);
			rectBtn.h = static_cast<int>(BUTTON_H*yScale);
			rectBtn.w = static_cast<int>((5 + MARGIN_X)*xScale);

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

			rectBtn.x += static_cast<int>((MARGIN_X + rectText.w)*xScale);
			rectBtn.h = static_cast<int>(BUTTON_H*yScale);
			rectBtn.w = static_cast<int>((5 + MARGIN_X)*xScale);

			rectTextureBtn.x = BUTTON_MAX_W - MARGIN_X;
			rectTextureBtn.y = 3*BUTTON_H + 3*BUTTON_SEPARATION;
			rectTextureBtn.h = BUTTON_H;
			rectTextureBtn.w = MARGIN_X;

			SDL_RenderCopy(renderer, bTexture, &rectTextureBtn, &rectBtn);

		}
	}
	rectBtn.w = static_cast<int>((2*MARGIN_X + rectText.w + 5)*xScale);
	setPosition(hold.x,hold.y);
	write(renderer,font,text,text_color,rectText,xScale, yScale);
};

/*===============================
MENU
===============================*/

mWindow::mWindow(void)
{
	loadFont(&font);
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

	menu = MENU_MAIN;

};

void mWindow::setup(SDL_Renderer* rend, SDL_Window *w, MENU m)
{
	renderer = rend;
	//image = const_cast<char*>(img.c_str());
	window = w;
	menu = m;

	int wWindow,hWindow;
	SDL_GetWindowSize(window,&wWindow,&hWindow);
	xScale = wWindow*1.0/WINDOW_INITIAL_W;
	yScale = hWindow*1.0/WINDOW_INITIAL_H;
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
	if (menu == MENU_MAIN)
	{
		x = static_cast<int>(MAIN_BTN_DEFAULT_X*xScale);
		y = static_cast<int>(MAIN_BTN_DEFAULT_Y*yScale);
		increment = static_cast<int>((BUTTON_H + BUTTON_SEPARATION)*yScale);
	}
	else if (menu == MENU_UNIT)
	{
		x = static_cast<int>((rectWin.x + UNIT_BTN_DEFAULT_X)*xScale);
		y = static_cast<int>((rectWin.y + UNIT_BTN_DEFAULT_Y)*yScale);
		//increment = static_cast<int>((BUTTON_H + BUTTON_SEPARATION)*yScale);
	}
	else if (menu == MENU_END_GAME){
		x = static_cast<int>(END_GAME_DEFAULT_X*xScale);
		y = static_cast<int>(END_GAME_DEFAULT_Y*yScale);
		increment = static_cast<int>((BUTTON_H + BUTTON_SEPARATION)*yScale);
	}
	else if (menu == MENU_UNIT_ACTION)
	{
		x = static_cast<int>((rectWin.x + UNIT_ACTION_DEFAULT_X)*xScale);
		y = static_cast<int>((rectWin.y + UNIT_ACTION_DEFAULT_Y)*yScale);
		increment = static_cast<int>((BUTTON_H + BUTTON_SEPARATION)*yScale);
	}
	btnX = x;
	btnY = y;
};

void mWindow::setTxtPosition()
{
	int x,y;
	if (menu == MENU_MAIN)
	{
		x = static_cast<int>((rectWin.x + MAIN_TXT_DEFAULT_X)*xScale);
		y = static_cast<int>((rectWin.y + MAIN_TXT_DEFAULT_Y)*yScale);
	}
	else if (menu == MENU_UNIT)
	{
		x = static_cast<int>((rectWin.x + UNIT_TXT_DEFAULT_X)*xScale);
		y = static_cast<int>((rectWin.y + UNIT_TXT_DEFAULT_Y)*yScale);
		increment = static_cast<int>((TEXT_H + LINE_SEPARATION)*yScale);
	}
	else if (menu == MENU_END_GAME) {
		x = static_cast<int>((rectWin.x + END_GAME_TXT_DEFAULT_X)*xScale);
		y = static_cast<int>((rectWin.y + END_GAME_TXT_DEFAULT_Y)*yScale);
		increment = static_cast<int>((TEXT_H + LINE_SEPARATION)*yScale);
	}
	else if (menu == MENU_UNIT_ACTION) {
		x = static_cast<int>((rectWin.x + UNIT_ACTION_TXT_DEFAULT_X)*xScale);
		y = static_cast<int>((rectWin.y + UNIT_ACTION_TXT_DEFAULT_Y)*yScale);
		//increment = static_cast<int>((TEXT_H + LINE_SEPARATION)*yScale);
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

bool mWindow::enableButton(int index){
	if (index > buttonList.size())
		return false;

	buttonList[index].enable();
	return true;
}

bool mWindow::disableButton(int index){
	if (index > buttonList.size())
		return false;

	buttonList[index].disable();
	return true;
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
	TTF_Font *title;
	loadTitle(&title);
	addText("TACTICS");
	textList[0].setFont(title);
	addButton("Start Game");
	addButton("Quit Game");
	setImage(MAIN_MENU_BKG);
	setScale();
	menu = MENU_MAIN;
	setBtnPosition();
	init(0,0);
};

void mWindow::statsMenu(
			unsigned int hp, 
			unsigned int maxHp, 
			unsigned int attackDamage, 
			unsigned int armor, 
			unsigned int level, 
			unsigned int move, 
			unsigned int range, 
			unsigned int actionPerTurn, 
			unsigned int mana, 
			unsigned int manaPool
			)
{
	stringstream ss,s;
	addText("Unit: ");
	addText("  Stats:");
	s << maxHp;
	ss << hp;
	addText("HP: " + ss.str() + "/" + s.str());
	ss.str("");
	ss << attackDamage;
	addText("AD: " + ss.str());
	ss.str("");
	ss << armor;
	addText("Armor: " + ss.str());
	ss.str("");
	ss << level;
	addText("Level: " + ss.str());
	ss.str("");
	ss << range;
	addText("Range: " + ss.str());
	ss.str("");
	ss << actionPerTurn;
	addText("Actions: " + ss.str());
	ss.str("");
	ss << move;
	addText("Move: " + ss.str());
	ss.str("");
	setTxtPosition();
	init(0,20);
};

void mWindow::endMenu(T_TEAM winningTeam,int turn){
	stringstream turnStr, teamStr;
	addText("Fim de jogo!");
	turnStr << turn;
	teamStr << (winningTeam == TEAM_A ? "A" : "B");
	addText("O time " + teamStr.str() + " venceu a partida no turno " + turnStr.str());

	addButton("Jogar novamente");

	disableButton(0);

	addButton("Sair");

	setImage(MAIN_MENU_BKG);
	setScale();
	menu = MENU_END_GAME;
	setTxtPosition();
	setBtnPosition();
	init(0,25);
}

void mWindow::unitActionMenu(int x,int y){
	menu = MENU_UNIT_ACTION;

	setImage(MAIN_MENU_BKG);
	setScale();
	init(0,150);
	setTxtPosition();
	setBtnPosition();

	addText("Escolha uma acao:");
	addButton("Mover");

	addButton("Atacar");
	addButton("Terminar turno");
	addButton("Cancelar");
}

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

		if(menu == MENU_MAIN)
		{
			SDL_RenderCopy(renderer, mTexture, NULL, NULL);

			textList[0].setPosition(xT,yT);
			textList[0].setScale(xScale,yScale);
			textList[0].show();

			for (unsigned i=0; i < buttonList.size(); i++)
			{
				buttonList[i].setPosition(xB,yB + increment*i);
				buttonList[i].setScale(xScale,yScale);
				buttonList[i].show(renderer);
			}
		}
		if(menu == MENU_UNIT)
		{

			SDL_Rect bck = {
				xT,
				yT,
				static_cast<int>(220*xScale),
				static_cast<int>(350*yScale)
			};

			SDL_Rect bckBorder = {
				bck.x+1,
				bck.y+1,
				bck.w-2,
				bck.h-2
			};

			SDL_SetRenderDrawColor(renderer,0,51,102,255);
			SDL_RenderFillRect(renderer,&bck);

			SDL_SetRenderDrawColor(renderer,58,63,78,255);
			SDL_RenderDrawRect(renderer,&bck);
			SDL_RenderDrawRect(renderer,&bckBorder);

			SDL_Color color = MENU_BLACK;
			for (unsigned i=0; i < textList.size(); i++)
			{
				textList[i].setColor(color);
				textList[i].setPosition(xT+10,yT + 20 + increment*i);
				textList[i].setScale(xScale,yScale);
				textList[i].show();
			}
		}
		else if (menu == MENU_END_GAME)
		{

			SDL_Rect bck = {
				END_GAME_TXT_DEFAULT_X-50,
				END_GAME_TXT_DEFAULT_Y-30,
				450,
				350
			};

			SDL_Rect bckBorder = {
				bck.x+1,
				bck.y+1,
				bck.w-2,
				bck.h-2
			};

			SDL_SetRenderDrawColor(renderer,0,51,102,255);
			SDL_RenderFillRect(renderer,&bck);

			SDL_SetRenderDrawColor(renderer,58,63,78,255);
			SDL_RenderDrawRect(renderer,&bck);
			SDL_RenderDrawRect(renderer,&bckBorder);

			SDL_Color color = MENU_BLACK;
			for (unsigned i=0; i < textList.size(); i++)
			{
				textList[i].setColor(color);
				textList[i].setPosition(xT,yT + increment*i);
				textList[i].setScale(xScale,yScale);
				textList[i].show();
			}

			for (unsigned i=0; i < buttonList.size(); i++)
			{
				buttonList[i].setPosition(xB,yB + (BUTTON_H + 10)*i);
				buttonList[i].setScale(xScale,yScale);
				buttonList[i].show(renderer);
			}

		}

		else if (menu == MENU_UNIT_ACTION)
		{
			SDL_Rect bck = {
				xT,
				yT,
				static_cast<int>(220*xScale),
				static_cast<int>(350*yScale)
			};

			SDL_Rect bckBorder = {
				bck.x+1,
				bck.y+1,
				bck.w-2,
				bck.h-2
			};

			SDL_SetRenderDrawColor(renderer,0,51,102,255);
			SDL_RenderFillRect(renderer,&bck);

			SDL_SetRenderDrawColor(renderer,58,63,78,255);
			SDL_RenderDrawRect(renderer,&bck);
			SDL_RenderDrawRect(renderer,&bckBorder);

			SDL_Color color = MENU_BLACK;
			for (unsigned i=0; i < textList.size(); i++)
			{
				if (&textList[i] != NULL) {
					textList[i].setColor(color);
					textList[i].setPosition(xT+10,yT + 20 + increment*i);
					textList[i].setScale(xScale,yScale);
					textList[i].show();
				}
			}
			for (unsigned i=0; i < buttonList.size(); i++)
			{
				//buttonList[i].setFont();
				buttonList[i].setPosition(xB + 10,yB + static_cast<int>(increment*i*0.75));
				buttonList[i].setScale(xScale*0.75,yScale*0.75);
				buttonList[i].show(renderer);
			}
		}
	}
};

void mWindow::setXY(int x, int y){
	rectWin.x = x;
	rectWin.y = y;

	setTxtPosition();
	setBtnPosition();
}

