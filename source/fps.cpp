#include "fps.h"

/*=============================
DRAW
==============================*/

void sdlInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
};

/*=============================
WRITE
==============================*/

void textInit()
{
	if (TTF_Init() != 0)
   {
      cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
      SDL_Quit();
      exit(1);
   }
};

void loadFont(TTF_Font **font)
{
    *font = TTF_OpenFont("images\\FinalFrontier.ttf", 24);
    if (font == NULL)
    {
	    cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
	    TTF_Quit();
	    SDL_Quit();
	    exit(1);
    }
};

SDL_Surface *textContent(TTF_Font *font,char *text,SDL_Color text_color)
{
	SDL_Surface *textSurface;
	textSurface = TTF_RenderText_Solid(font,
   	text,
   	text_color);

   	if (textSurface == NULL)
   	{
      	cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << "\nVendo o erro:\nstring = " << text << endl;
      	TTF_Quit();
      	SDL_Quit();
      	exit(1);
   	}
   	return textSurface;
};

void write(
	SDL_Renderer* renderer,
	TTF_Font *font, 
	string text,
	SDL_Color text_color,
	SDL_Rect rectText
	)
{
	SDL_Texture *tTexture;
	SDL_Surface *tSurface;

	int w=0,h=0;

    tSurface = textContent(font,const_cast<char*>(text.c_str()),text_color);
    tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);
    SDL_FreeSurface(tSurface);
    rectText.w=w;
    rectText.h=h;

    SDL_RenderCopy(renderer, tTexture, NULL, &rectText);
};

SDL_Rect write(
	SDL_Renderer* renderer,
	TTF_Font *font, 
	string text,
	SDL_Color text_color,
	SDL_Rect rectText,
	float scale
	)
{
	SDL_Texture *tTexture;
	SDL_Surface *tSurface;

	int w,h;
	float wF,hF;

    tSurface = textContent(font,const_cast<char*>(text.c_str()),text_color);
    tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);
    SDL_FreeSurface(tSurface);

    wF = w*scale;
    hF = h*scale;
    w = (int)wF;
    h = (int)hF;

    rectText.w=w;
    rectText.h=h;

    SDL_RenderCopy(renderer, tTexture, NULL, &rectText);

    return rectText;
};

SDL_Rect simWrite(
	SDL_Renderer* renderer,
	TTF_Font *font, 
	string text,
	SDL_Color text_color,
	SDL_Rect rectText,
	float scale
	)
{
	SDL_Texture *tTexture;
	SDL_Surface *tSurface;

	int w,h;
	float wF,hF;

    tSurface = textContent(font,const_cast<char*>(text.c_str()),text_color);
    tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);
    SDL_FreeSurface(tSurface);

    wF = w*scale;
    hF = h*scale;
    w = (int)wF;
    h = (int)hF;

    rectText.w=w;
    rectText.h=h;

    //SDL_RenderCopy(renderer, tTexture, NULL, &rectText);

    return rectText;
};

/*=============================
FPS
==============================*/

//CONSTRUTOR
framesPerSecond::framesPerSecond(void)
{
	loop = 0.000000000;
	start = 0;
	end = 0;
	frames = 0;
	fps = 0.00;
	rect.x = 0;
	rect.y = 0;
	rect.h = 0;
	rect.w = 0;
};

//SET VARIABLES
void framesPerSecond::setFrames(int f)
{
	frames = f;
};
time_t framesPerSecond::setStart()
{
	start = time(NULL);
	return start;
};
time_t framesPerSecond::setEnd()
{
	end = time(NULL);
	return end;
};

//GET VARIABLES
int framesPerSecond::getFrames()
{
	return frames;
};

SDL_Rect framesPerSecond::getRect()
{
	return rect;
};

double framesPerSecond::getLoop()
{
	return loop;
};

//FUNCTIONS:
void framesPerSecond::plus()
{
	frames++;
};

double framesPerSecond::calculate()
{
	loop += difftime(end,start);
	fps = frames;
	return fps;
};
void framesPerSecond::show(SDL_Renderer* renderer, TTF_Font *font)	
{
	SDL_Rect rectText;
	SDL_Color text_color = {255, 255, 255};
	string text;

	ostringstream strStream;   // float to std::string
    strStream << fps;
    string strFPS(strStream.str());

	text = "FPS: " + strFPS;

    rectText.x = 0;
    rectText.y = 0;

    rect = rectText;

    write(renderer,font,text,text_color,rect);

};
void framesPerSecond::fpsControl(int limit_fps) {
	frameDuration = (float) 1000/limit_fps;
	lastTick = SDL_GetTicks();
};
bool framesPerSecond::isFrameDone(){
	float currentTick = SDL_GetTicks();
	float duration = currentTick - lastTick;
	if (duration >= frameDuration){
		lastTick = currentTick;
		return true;
	}
	return false;
};
