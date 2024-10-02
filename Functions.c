#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "Functions.h"

void InitSDL(SDL_Window** Window, SDL_Renderer** Render)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *Window = SDL_CreateWindow("Première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_FULLSCREEN);

    if(!(*Window))
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *Render = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);

    if(!(*Render))
    {
        SDL_Log("Erreur : Initialisation Renderer > %s\n", SDL_GetError());
        SDL_DestroyWindow(*Window);
        exit(EXIT_FAILURE);
    }
}

double complex PixelConvert(int Px, int Py)
{
    return (Px*((Xmax - Xmin)/W) + Xmin) + (Py*((Ymax - Ymin)/H) + Ymin)*I;;
}

float VectNorm(double complex z)
{
    return csqrt(creal(z)*creal(z) + cimag(z)*cimag(z));
}

int Sequence(double complex c)
{
    double complex z = 0;
    int j = -1;

    while(j<iMax && VectNorm(z)<=2)
    {
        z = z*z + c;
        j++;
    }

    return j;
}

void DrawPixelColor(SDL_Renderer* Render, int i, int c, int l)
{
    Uint8 R = 0;
    Uint8 G = 0;
    Uint8 B = 0;
    Uint8 A = 255;
    
    if(i<iMax)
    {
        float KR = (2*M_PI)/50; // /50
        float KG = (2*M_PI)/50;
        float KB = (2*M_PI)/50;

        R = (Uint8)((255/2) * (1 + sin(KR*i)));
        G = (Uint8)((255/2) * (1 + sin(KG*i + M_PI/2)));
        B = (Uint8)((255/2) * (1 + sin(KB*i + M_PI)));
    }
    
    SDL_SetRenderDrawColor(Render, R, G, B, A);
    SDL_RenderDrawPoint(Render, c, l);
}


void RenderFractal(SDL_Renderer* Render)
{
    int l, c;
    double complex z = 0;

    for(l=0; l<H; l++)
    {
        for(c=0; c<W; c++)
        {    
            z = PixelConvert(c, l);
            DrawPixelColor(Render, Sequence(z), c, l);
        }
    }
    
    SDL_RenderPresent(Render);
}