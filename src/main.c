#include <stdio.h>
#include <complex.h>
#include <SDL2/SDL.h>
#include "Functions.h"

int main( int argc, char* argv[] )
{
    SDL_Window *window = NULL;
    SDL_Renderer *Render = NULL;
    SDL_Event Event;
    int Run = 1;

    InitSDL(&window, &Render);

    RenderFractal(Render);
    printf("> Generation completed\n\n");

    while(Run)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
                Run = 0;
            
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    Run = 0;
            }
        }
    }

    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}