/*#include "animation.h"


void textInit();
{
	if (TTF_Init() != 0)
   {
      cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
      SDL_Quit();
      exit(1);
   }
}

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
		}

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
