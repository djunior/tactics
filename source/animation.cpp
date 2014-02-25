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

TTF_Font *loadFont()
{
	TTF_Font *font;
    font = TTF_OpenFont("images\\FinalFrontier.ttf", 24);
    if (font == NULL)
    {
	    cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
	    TTF_Quit();
	    SDL_Quit();
	    exit(1);
    }
    return font;
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
	_loop = 0.000000000;
	_start = 0;
	_end = 0;
	_frames = 0;
	_fps = 0.00;
	_rect.x = 0;
	_rect.y = 0;
	_rect.h = 0;
	_rect.w = 0;
};
void framesPerSecond::setFrames(int f)
{
	_frames = f;
};

int framesPerSecond::getFrames()
{
	return _frames;
};

SDL_Rect framesPerSecond::getRect()
{
	return _rect;
};
time_t framesPerSecond::start()
{
	_start = time(NULL);
	return _start;
};
time_t framesPerSecond::end()
{
	_end = time(NULL);
	return _end;
};
double framesPerSecond::getLoop()
{
	return _loop;
};

//FUNCTIONS:
void framesPerSecond::plus()
{
	_frames++;
};

double framesPerSecond::calculate()
{
	_loop += difftime(_end,_start);
	_fps = _frames;
	return _fps;
};
SDL_Texture *framesPerSecond::show(SDL_Renderer* renderer, TTF_Font *font)	
{
	SDL_Texture *tTexture;
	SDL_Rect rectText;
	SDL_Surface *tSurface;
	SDL_Color text_color = {255, 255, 255};
	char cText[10];
	int w=0,h=0;
	string text;

	ostringstream strStream;   // float to std::string
    strStream << _fps;
    string strFPS(strStream.str());

	text = "FPS: " + strFPS;

	strncpy(cText, text.c_str(), sizeof(cText));

    tSurface = textContent(font,cText,text_color);
    tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_QueryTexture(tTexture, NULL, NULL, &w, &h);
    rectText.x = 0;
    rectText.y = 0;
    rectText.w = w;
    rectText.h = h;
    _rect = rectText;

    return tTexture;
};
