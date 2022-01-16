#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Window.hh"
#include "Renderer.hh"
#include "Globals.hh"
#include "Board.hh"
#include "ScreenSize.hh"

#define FPS 60

int main(int argc, char* argv[])
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    unsigned int frameTime;

    SDL_Init(SDL_INIT_EVERYTHING);

    // create window and renderer
    Window window;

	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) &imgFlags))
		std::cout << "SDL_image could not initialize! " << IMG_GetError() << "\n";

	// initialize board
	board = new Board;

    // event handler
    SDL_Event e;

    // Game loop:
    while (!applicationShouldClose)
    {
        // handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            // user requests quit
            if(e.type == SDL_QUIT)
                applicationShouldClose = true;
        }

        frameStart = SDL_GetTicks();

        Update();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);

    }

	SDL_DestroyTexture(board->getBoard());
	Quit();


    return 0;

}

void Update()
{
    Render(Renderer::get());
}

void Render(SDL_Renderer* ren)
{
    // draw white screen
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(ren);
    // Draw board
    // Draw Background
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderCopy(ren, board->getBoard(), nullptr, (const SDL_Rect *) Screen::width);
    // update screen
    SDL_RenderPresent(ren);
}


void Quit()
{
	// close SDL
	IMG_Quit();
    SDL_Quit();
}
