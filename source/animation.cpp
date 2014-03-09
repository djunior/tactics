#include "animation.h"

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
    cerr << *font << endl;
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
SDL_Texture *framesPerSecond::show(SDL_Renderer* renderer, TTF_Font *font)	
{
	SDL_Texture *tTexture;
	SDL_Rect rectText;
	SDL_Surface *tSurface;
	SDL_Color text_color = {255, 255, 255};
	int w=0,h=0;
	string text;

	ostringstream strStream;   // float to std::string
    strStream << fps;
    string strFPS(strStream.str());

	text = "FPS: " + strFPS;

    tSurface = textContent(font,const_cast<char*>(text.c_str()),text_color);
    tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);
    rectText.x = 0;
    rectText.y = 0;
    rectText.w = w;
    rectText.h = h;
    rect = rectText;

    SDL_FreeSurface(tSurface);

    return tTexture;
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
