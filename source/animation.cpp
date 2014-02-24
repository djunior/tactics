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

SDL_Surface *textContent(TTF_Font *font,const char *text,SDL_Color text_color)
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
==============================
class framesPerSecond
{
	private:
		int _frames;
		time_t _start;
		time_t _end;
		double _loop;

	public:
		// SET Variables:
		void frames(int f){_frames = f;};
		void start(time_t s){_start = s};
		void end(time_t e){_end = e};
		void loop()
		{
			_loop += difftime(_end,_start);
		};
		// GET Variables:
		int frames(){return _frames;};
		time_t start(){return _start;};
		time_t end(){return _end;};
		double loop(){return _loop;};

		//FUNCTIONS:
		void plus()
		{
			_frames++;
		};

		int calculate()
		{
			int fps;
			_loop = difftime(_end,_start);
			fps = _frames/_loop;
			return fps;
		};
		show()

		//CONSTRUTOR
		framesPerSecond::framesPerSecond()
		{
			_loop = 0.000000000;
			_start = 0;
			_end = 0;
			_frames = 0;
		};
};*/

