/*
 * main.c
 *
 *	Projeto Tactics
 *
 *  Created on: Feb 12, 2014
 *      Author: djunior
 */
#include "basic_includes.h"

#include "animation.h"

#include "board.h"
#include "gameManager.h"
#include "unit.h"

//#include <thread>
//#include <chrono>

int main(int argc, char *argv[]){

    sdlInit();
    textInit();

    bool Running = true;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event Event;

    SDL_Texture *Map,*Char;
    SDL_Rect rectMap,rectChar;

    TTF_Font *font;

    framesPerSecond fps;
    Board gameBoard(8,8);
    GameManager gm(&gameBoard);


    // OnInit

    window = SDL_CreateWindow("Tactics", 100, 100, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC);
	if (window == 0){
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL){
        cout << SDL_GetError() << endl;
        return 1;
    }

    //Load Content
    int w=0,h=0;
    Map = IMG_LoadTexture(renderer,"images\\mapa.jpg");
    SDL_QueryTexture(Map, NULL, NULL, &w, &h);
    rectMap.x = 0;
    rectMap.y = 0;
    rectMap.w = w;
    rectMap.h = h;

    Char = IMG_LoadTexture(renderer, "images\\char_lanca.png");
    SDL_QueryTexture(Char, NULL, NULL, &w, &h);
    rectChar.x = 350;
    rectChar.y = 200;
    rectChar.w = w/2;
    rectChar.h = h;

    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=w/4;
    src.h=h/2;
    
    // FPS Setup BEGIN

    loadFont(&font);  

    fps.fpsControl(60);
    
    fps.setFrames(0);
    time_t hold;
    time_t actual;
    hold = fps.setStart();
    actual = hold;

    // FPS Setup END

    // Unit create BEGIN
    cerr << "Criando unidade 1!" << endl;
    gm.createUnit("wizard",TEAM_A);

    cerr << "Criando unidade 2!" << endl;
    gm.createUnit("wizard",TEAM_B);

    //gameBoard.debug_showMap();
    //gm.startGame();

    // Unit create END

    while (Running) 
    {

    	if (fps.isFrameDone()) {

			while(SDL_PollEvent(&Event))
			{
				switch(Event.type)
				{
					case SDL_QUIT:
						Running = false;
						break;

					case SDL_KEYDOWN:
						switch(Event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								Running = false;
								break;
							case SDLK_RIGHT:
								rectChar.x+=10;
								break;
							case SDLK_LEFT:
								rectChar.x-=10;
								break;
						}
						break;

				}
			}


			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, Map, NULL, &rectMap);
			SDL_RenderCopy(renderer, Char, &src, &rectChar);

			//FPS BEGIN

			fps.plus();
			if (actual != hold)
			{
				fps.calculate();
				fps.setFrames(0);
				hold = fps.setEnd();

			}
			else
			{
				actual = fps.setEnd();
			}
			fps.show(renderer,font);

			//FPS END


		/*
			David: forma mais gambiarra de implementar limitação de fps em 60 fps

			utilizar um sleep de 1/60 segundos

			para isso, utilizar a biblioteca thread e chrono

			acrescentar os includes:
			<thread>
			<chrono>

			e logo abaixo desse comentario fazer:

			std::this_thread::sleep_for(std::chrono::seconds(1/60));

			Mais informações sobre essa função em: http://www.cplusplus.com/reference/thread/this_thread/sleep_for/
			http://www.cplusplus.com/reference/chrono/ também pode ser útil em caso de dúvidas.

			Para tornar esse controle mais valido, pode-se estimar o tempo que o pc leva para desenhar um quadro.
			Considerando que o codigo de contagem de fps do jack estava resultado aproximadamente 3k a 4k fps,
			podemos fazer:

			std::this_thread::sleep_for(std::chrono::seconds(1/60 - 1/3500));

			A solução final seria medir o tempo do inicio do loop e subtrair o tempo apos realizar as operações
			de pintura, dessa forma calculando o tempo de cada frame e nao estimando, como foi feito acima.

			Também é interessante utilizar SDLBlit e SDL_Flip para otimizar esse processo.

			Esse sleep deveria forçar o tempo de pintura de cada quadro para algo próximo a 1/60 segundos,
			o que resulta em 60 fps.

		*/
		  //  std::this_thread::sleep_for(std::chrono::seconds(1/60 - 1/3500));

			SDL_RenderPresent(renderer);
    	}
    }

	SDL_Quit();
	return EXIT_SUCCESS;
}

