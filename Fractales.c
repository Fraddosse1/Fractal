#include <stdio.h>
#include <complex.h>
#include <SDL2/SDL.h>
#include "Functions.c"

// Compile command : gcc -I src/include -L src/lib -o main Fractales.c -lmingw32 -lSDL2main -lSDL2
// Execute : ./main

int main( int argc, char* argv[] )
{
    SDL_Window *window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);

    if(!window)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Renderer *Render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!Render)
    {
        SDL_Log("Erreur : Initialisation Renderer > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    RenderFractal(Render, 500, 1080, 1920, 1, -2, 1, -1);
    SDL_RenderPresent(Render);
    printf("> End of generation\n");

    int Run = 1;
    SDL_Event Event;

    while(Run)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
                Run = 0;
        }
    }

    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}