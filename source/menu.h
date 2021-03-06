#ifndef menu_h
#define menu_h

#include "basic_includes.h"
#include "mouse.h"
#include "utils/t_team.h"
#include <vector>

#define MARGIN_X 20
#define MARGIN_Y 15

#define BUTTON_H 50
#define BUTTON_MAX_W 600
#define BUTTON_SEPARATION 20

#define TEXT_H 23
#define LINE_SEPARATION 10

#define MAIN_BTN_DEFAULT_X 300
#define MAIN_BTN_DEFAULT_Y 200
#define MAIN_TXT_DEFAULT_X 250
#define MAIN_TXT_DEFAULT_Y 50

#define UNIT_BTN_DEFAULT_X 10
#define UNIT_BTN_DEFAULT_Y 150
#define UNIT_TXT_DEFAULT_X 0
#define UNIT_TXT_DEFAULT_Y 10

#define UNIT_MENU_MAX_X 200
#define UNIT_MENU_MAX_Y 350

#define END_GAME_DEFAULT_X 0
#define END_GAME_DEFAULT_Y 200
#define END_GAME_TXT_DEFAULT_X 250
#define END_GAME_TXT_DEFAULT_Y 50

#define UNIT_ACTION_TXT_DEFAULT_X 0
#define UNIT_ACTION_TXT_DEFAULT_Y 200
#define UNIT_ACTION_DEFAULT_X 0
#define UNIT_ACTION_DEFAULT_Y 250

#define SELECTED {255,255,255}
#define NOT_SELECTED {70,70,70}
#define MENU_BLACK {0,0,0}

#define BUTTON_IMG "images\\btn_blue_sprite.gif"
#define MAIN_MENU_BKG "images\\fft_wallpaper.png"

enum MENU_ENUM {
	MENU_MAIN,
	MENU_UNIT,
	MENU_TOOTIP,
	MENU_END_GAME,
	MENU_UNIT_ACTION,
	MENU_GAME_CONFIG,
};

enum TEXTLIST_POSITION {
	TEXTLIST_UNIT,
	TEXTLIST_STATS,
	TEXTLIST_HP,
	TEXTLIST_AD,
	TEXTLIST_ARMOR,
	TEXTLIST_LVL,
	TEXTLIST_RANGE,
	TEXTLIST_APT,
	TEXTLIST_MOVE,
};

typedef enum MENU_ENUM MENU;
typedef enum TEXTLIST_POSITION TEXTLIST_POSITION;

class mText
{
	private:
		TTF_Font *font;
		string text;
		SDL_Color text_color;
		SDL_Renderer* renderer;
		float xScale, yScale;
		SDL_Rect rectText;
		MENU menu;
	public:
		mText(SDL_Renderer*,TTF_Font*,string,SDL_Color,float);
		void setScale(float,float);
		void setFont(TTF_Font*);
		void setText(string);
		void setColor(SDL_Color);
		void setPosition(int,int);
		void show();
		SDL_Rect getRect();
};

class mButton
{
	private:
		bool isSelected;
		bool isEnabled;
		SDL_Rect rectBtn;
		SDL_Rect rectTextureBtn;
		SDL_Texture *bTexture;
		string text;
		SDL_Color text_color;
		TTF_Font *font;
		float xScale, yScale;

	public:
		mButton(SDL_Renderer*, TTF_Font*);
		mButton(SDL_Renderer*, TTF_Font*, int, int);
		mButton(SDL_Renderer*, TTF_Font*, int, int, string);
		void setScale(float,float);
		void setFont();
		void setIsSelected(bool);
		void setPosition(int,int);
		void setColor(SDL_Color);
		void setText(string);
		void setText(float);
		SDL_Rect getRect();
		string getText();
		bool bHit();
		void show(SDL_Renderer*);
		void disable();
		void enable();
};

class mWindow
{
	private:
		bool isOpen;
		const char* image;
		int btnX;
		int btnY;
		int txtX;
		int txtY;
		int increment;
		TTF_Font *font;
		SDL_Renderer* renderer;
		SDL_Rect rectWin;
		SDL_Texture *mTexture;
		SDL_Window* window;
		float xScale;
		float yScale;
		MENU menu;
		vector<mButton> buttonList;

	public:
		mWindow(void);
		mWindow(TTF_Font *,SDL_Renderer*,SDL_Window*);
		void setup(SDL_Renderer*,SDL_Window*,MENU);
		void setScale();
		void setIsOpen(bool);
		void setRectWin(SDL_Rect);
		void setImage(string);
		void setBtnPosition();
		void setTxtPosition();
		bool getIsOpen();
		SDL_Rect getRectWin();
		int btnHit();
		void addButton(string);
		void addText(string);
		void init(int,int);
		void mainMenu();
		void unitActionMenu(int,int);
		void endMenu(T_TEAM winningTeam,int turn);
		void gameConfigMenu();
		void statsMenu(
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
			);
		void show();
		void setXY(int,int);
		vector<mText> textList;
		bool enableButton(int);
		bool disableButton(int);
};

#endif
